// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "client.h"

int sndmsg(char msg[1024], int port) {
    // Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        return -1;
    }

    // Specify the server address to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_LOOPBACK;  // Connect to the local machine

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error connecting to server");
        close(client_socket);
        return -1;
    }

    // Send the message to the server
    ssize_t bytes_sent = send(client_socket, msg, strlen(msg), 0);
    if (bytes_sent < 0) {
        perror("Error sending message");
        close(client_socket);
        return -1;
    }

    // Close the client socket
    close(client_socket);

    printf("Message sent to server: %s\n", msg);

    return 0;
}
