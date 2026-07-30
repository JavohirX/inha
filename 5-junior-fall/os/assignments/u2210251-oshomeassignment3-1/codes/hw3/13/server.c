// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 2048

static int client_count = 0;
static int client_sockets[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void send_message_to_all(char *message, int sender_sd) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] != 0 && client_sockets[i] != sender_sd) {
            send(client_sockets[i], message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_server_input(void *arg) {
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE + 32];
    
    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);
        sprintf(message, "Server: %s", buffer);
        printf("\033[1;32m%s\033[0m", message); // Print in green color
        send_message_to_all(message, -1);
    }
    return NULL;
}

void *handle_client(void *arg) {
    int client_sd = *((int *)arg);
    free(arg);
    char buffer[BUFFER_SIZE];
    char notification[BUFFER_SIZE];
    
    // Send welcome message
    sprintf(notification, "Client #%d joined the chat!\n", client_sd);
    send_message_to_all(notification, client_sd);
    printf("%s", notification);
    
    while (1) {
        int bytes_received = recv(client_sd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            pthread_mutex_lock(&clients_mutex);
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == client_sd) {
                    client_sockets[i] = 0;
                    break;
                }
            }
            client_count--;
            pthread_mutex_unlock(&clients_mutex);
            
            sprintf(notification, "Client #%d left the chat.\n", client_sd);
            send_message_to_all(notification, client_sd);
            printf("%s", notification);
            close(client_sd);
            return NULL;
        }
        
        buffer[bytes_received] = '\0';
        char message[BUFFER_SIZE + 32];
        sprintf(message, "Client #%d: %s", client_sd, buffer);
        send_message_to_all(message, client_sd);
        printf("%s", message);
    }
    return NULL;
}

int main() {
    int server_sd;
    struct sockaddr_in server_addr;
    
    // Create socket
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Enable address reuse
    int opt = 1;
    if (setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(1);
    }
    
    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    // Bind socket
    if (bind(server_sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        exit(1);
    }
    
    // Listen for connections
    if (listen(server_sd, 10) < 0) {
        perror("Listen failed");
        exit(1);
    }
    
    printf("Chat server started. Listening on port 9999...\n");
    printf("Type your messages and press Enter to send to all clients.\n\n");
    
    // Initialize client sockets array
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = 0;
    }
    
    // Create thread for server input
    pthread_t server_tid;
    pthread_create(&server_tid, NULL, handle_server_input, NULL);
    
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        // Accept new connection
        int client_sd = accept(server_sd, (struct sockaddr *)&client_addr, &client_len);
        if (client_sd < 0) {
            perror("Accept failed");
            continue;
        }
        
        // Print client IP address
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        printf("New connection from %s:%d\n", client_ip, ntohs(client_addr.sin_port));
        
        if (client_count >= MAX_CLIENTS) {
            printf("Maximum clients reached. Connection rejected.\n");
            close(client_sd);
            continue;
        }
        
        // Add client socket to array
        pthread_mutex_lock(&clients_mutex);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i] == 0) {
                client_sockets[i] = client_sd;
                break;
            }
        }
        client_count++;
        pthread_mutex_unlock(&clients_mutex);
        
        // Create thread for client
        pthread_t tid;
        int *pclient = malloc(sizeof(int));
        *pclient = client_sd;
        pthread_create(&tid, NULL, handle_client, pclient);
        pthread_detach(tid);
    }
    
    close(server_sd);
    return 0;
}
