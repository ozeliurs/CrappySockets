//
// Created by Maxime BILLY on 03/01/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_PORT_LENGTH 6  // Maximum length for a port number (including null terminator)

char pipe_path[32];  // File path for the named pipe

int server_fd = -1;  // File descriptor for the server named pipe

int startserver(int port) {
    // Create the named pipe path based on the port
    sprintf(pipe_path, "/tmp/crappy_sockets_%d.sock", port);

    // Create the named pipe
    if (mkfifo(pipe_path, 0666) == -1) {
        perror("Error creating named pipe");
        return -1;
    }

    // Open the named pipe for reading and writing
    server_fd = open(pipe_path, O_RDWR);
    if (server_fd == -1) {
        perror("Error opening named pipe");
        return -1;
    }

    return 0;
}

int stopserver() {
    // Close and unlink the named pipe
    if (close(server_fd) == -1 || unlink(pipe_path) == -1) {
        perror("Error closing/unlinking named pipe");
        return -1;
    }

    return 0;
}

int getmsg(char msg_read[1024]) {
    // Read a message from the named pipe
    ssize_t bytes_read = read(server_fd, msg_read, 1023);

    if (bytes_read == -1) {
        perror("Error reading from named pipe");
        return -1;
    }

    // Null-terminate the string
    msg_read[bytes_read] = '\0';

    return bytes_read;
}