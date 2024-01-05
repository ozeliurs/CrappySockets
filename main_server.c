//
// Created by Maxime BILLY on 03/01/2024.
//

// main_server.c

#include "server.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    int port = 8080;

    startserver(port);

    printf("Server started on port %d\n", port);

    char msg_read[1024];
    int bytesRead = getmsg(msg_read);

    if (bytesRead < 0) {
        fprintf(stderr, "Failed to read message from client\n");
        stopserver();  // Ensure to stop the server even if an error occurs
        return 1;
    }

    printf("Message from client: %s\n", msg_read);

    // Stop the server
    stopserver();

    printf("Server stopped\n");

    return 0;
}
