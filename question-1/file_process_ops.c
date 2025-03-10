#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    // File operations
    int fd = open("test.txt", O_CREAT | O_WRONLY, 0644);
    write(fd, "Hello, World!\n", 14);
    close(fd);

    // Process operations
    pid_t pid = fork();
    if (pid == 0) {
        execlp("ls", "ls", "-l", NULL);
        perror("exec");
        exit(1);
    } else {
        wait(NULL);
        printf("Child process completed.\n");
    }
    return 0;
}
