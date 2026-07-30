// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 2048

void *receive_messages(void *arg) {
    int socket_desc = *((int *)arg);
    char buffer[BUFFER_SIZE];
    
    while (1) {
        int bytes_received = recv(socket_desc, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            printf("\nServer disconnected.\n");
            exit(1);
        }
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }
    return NULL;
}

int main() {
    int socket_desc;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    
    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    
    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = inet_addr("172.28.186.78");
    
    // Connect to server
    if (connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }
    
    printf("Connected to chat server!\n");
    
    // Create thread for receiving messages
    pthread_t tid;
    int *pclient = malloc(sizeof(int));
    *pclient = socket_desc;
    pthread_create(&tid, NULL, receive_messages, pclient);
    
    // Main loop for sending messages
    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);
        if (send(socket_desc, buffer, strlen(buffer), 0) < 0) {
            perror("Send failed");
            break;
        }
    }
    
    close(socket_desc);
    return 0;
}