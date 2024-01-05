#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Function to generate the named pipe path based on the port
char *get_pipe_path(int port) {
    if (port > 65535) {
        perror("Port number too high");
        exit(-1);
    }
    char *pipe_path = malloc(32);
    sprintf(pipe_path, "/tmp/crappy_sockets_%d.sock", port);
    return pipe_path;
}

int sndmsg(char msg[1024], int port) {
    char *pipe_path = get_pipe_path(port);

    // Open the named pipe for writing
    int client_fd = open(pipe_path, O_WRONLY);
    if (client_fd == -1) {
        perror("Error opening named pipe for writing");
        free(pipe_path);
        return -1;
    }

    // Write the message to the named pipe
    ssize_t bytes_written = write(client_fd, msg, strlen(msg));

    if (bytes_written == -1) {
        perror("Error writing to named pipe");
        close(client_fd);
        free(pipe_path);
        return -1;
    }

    // Close the named pipe
    if (close(client_fd) == -1) {
        perror("Error closing named pipe");
        free(pipe_path);
        return -1;
    }

    free(pipe_path);
    return 0;
}
