// filename: forkchild.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // fork, exec
#include <sys/types.h>
#include <sys/wait.h> // wait

int main() {
    pid_t pid = fork(); // create child process

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Child process: executing 'ls'\n");
        execlp("ls", "ls", "-l", NULL); // run ls -l
        perror("execlp failed");        // only runs if execlp fails
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        wait(NULL); // wait for child to finish
        printf("Parent process: child finished.\n");
    }

    return 0;
}
