// filename: copyfilesyscall.c
#include <stdio.h>
#include <fcntl.h>   // open
#include <unistd.h>  // read, write, close
#include <stdlib.h>  // exit

#define BUFFER_SIZE 1024

int main() {
    int fd_src, fd_dest;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Open source file
    fd_src = open("result.txt", O_RDONLY);
    if (fd_src < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open/create destination file
    fd_dest = open("result.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest < 0) {
        perror("Error opening destination file");
        close(fd_src);
        exit(EXIT_FAILURE);
    }

    // Read and write loop
    while ((bytes_read = read(fd_src, buffer, BUFFER_SIZE)) > 0) {
        if (write(fd_dest, buffer, bytes_read) != bytes_read) {
            perror("Write error");
            close(fd_src);
            close(fd_dest);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read < 0) {
        perror("Read error");
    }

    close(fd_src);
    close(fd_dest);

    printf("File copied successfully!\n");
    return 0;
}
