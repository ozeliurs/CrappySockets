//
// Created by Maxime BILLY on 03/01/2024.
//

#include "server.h"

// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Assuming you have a global variable for the server socket
int server_socket;

int startserver(int port) {
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        return -1;
    }

    // Bind to a specific port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        close(server_socket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Error listening for connections");
        close(server_socket);
        return -1;
    }

    printf("Server started on port %d\n", port);

    return 0;
}

int stopserver() {
    // Close the server socket
    close(server_socket);
    printf("Server stopped\n");
    return 0;
}

int getmsg(char msg_read[1024]) {
    // Accept a connection
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
    if (client_socket < 0) {
        perror("Error accepting connection");
        return -1;
    }

    // Read message from the client
    ssize_t bytes_received = recv(client_socket, msg_read, 1024, 0);
    if (bytes_received < 0) {
        perror("Error receiving message");
        close(client_socket);
        return -1;
    }

    // Close the client socket
    close(client_socket);

    // Null-terminate the received message
    msg_read[bytes_received] = '\0';

    printf("Received message: %s\n", msg_read);

    return 0;
}

