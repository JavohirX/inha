#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define MAX_BUFFER 2048
#define PORT 9999
#define MAX_CLIENTS 10

// Global variables for cleanup
volatile sig_atomic_t server_running = 1;
int server_socket;

// Function prototypes
void *connection_handler(void *);
void handle_shutdown(int sig);

int main(int argc, char *argv[]) {
    int new_socket, client_len;
    struct sockaddr_in server, client;
    
    // Setup signal handler for graceful shutdown
    signal(SIGINT, handle_shutdown);
    
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Could not create socket");
        return 1;
    }
    
    // Set socket options for reuse
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        return 1;
    }
    
    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(9999);
    
    // Bind
    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }
    printf("Bind done on port %d\n", 9999);
    
    // Listen
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        return 1;
    }
    printf("Waiting for incoming connections...\n");
    
    client_len = sizeof(struct sockaddr_in);
    
    while (server_running) {
        new_socket = accept(server_socket, (struct sockaddr *)&client, (socklen_t*)&client_len);
        if (new_socket < 0) {
            if (server_running) {
                perror("Accept failed");
            }
            continue;
        }
        
        printf("Connection accepted from %s:%d\n", 
               inet_ntoa(client.sin_addr), 
               ntohs(client.sin_port));
        
        // Create new thread data
        int *new_sock = malloc(sizeof(int));
        if (new_sock == NULL) {
            perror("Failed to allocate memory");
            close(new_socket);
            continue;
        }
        *new_sock = new_socket;
        
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, connection_handler, (void*)new_sock) < 0) {
            perror("Could not create thread");
            free(new_sock);
            close(new_socket);
            continue;
        }
        
        // Detach thread to allow it to clean up automatically
        pthread_detach(thread_id);
    }
    
    close(server_socket);
    return 0;
}

void *connection_handler(void *socket_desc) {
    int sock = *(int*)socket_desc;
    char message[MAX_BUFFER];
    char client_message[MAX_BUFFER];
    char server_response[MAX_BUFFER];
    ssize_t read_size;
    
    // Welcome message
    snprintf(message, sizeof(message), 
             "Welcome! You are connected to socket %d\n", sock);
    if (send(sock, message, strlen(message), 0) < 0) {
        goto cleanup;
    }
    
    // Chat loop
    while (1) {
        // Clear buffers
        memset(client_message, 0, sizeof(client_message));
        memset(server_response, 0, sizeof(server_response));
        
        // Receive message
        read_size = recv(sock, client_message, sizeof(client_message) - 1, 0);
        if (read_size <= 0) {
            if (read_size == 0) {
                printf("Client disconnected\n");
            } else {
                perror("recv failed");
            }
            break;
        }
        
        // Remove newline if present
        client_message[strcspn(client_message, "\n")] = 0;
        
        printf("From Client [%d]: %s\n", sock, client_message);
        
        // Check for exit command
        if (strcmp(client_message, "bye") == 0) {
            printf("Client requested to exit\n");
            break;
        }
        
        // Get server response
        printf("Server response for client [%d]: ", sock);
        if (fgets(server_response, sizeof(server_response), stdin) == NULL) {
            break;
        }
        
        // Format and send response
        snprintf(message, sizeof(message), "Server to [%d]: %s", 
                sock, server_response);
        if (send(sock, message, strlen(message), 0) < 0) {
            perror("Send failed");
            break;
        }
    }
    
cleanup:
    close(sock);
    free(socket_desc);
    printf("Handler for socket %d cleaned up and exiting\n", sock);
    return NULL;
}

void handle_shutdown(int sig) {
    printf("\nShutting down server...\n");
    server_running = 0;
    close(server_socket);
}
