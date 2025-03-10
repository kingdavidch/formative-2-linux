#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        write(STDERR_FILENO, "Usage: copy <src> <dest>\n", 25);
        return 1;
    }

    char buffer[4096];
    int src = open(argv[1], O_RDONLY);
    int dest = open(argv[2], O_WRONLY | O_CREAT, 0644);
    ssize_t bytesRead;

    while ((bytesRead = read(src, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, bytesRead);
    }

    close(src);
    close(dest);
    return 0;
}
