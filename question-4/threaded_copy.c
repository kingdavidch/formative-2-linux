#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

typedef struct {
    int src_fd;
    int dest_fd;
    off_t start;
    off_t end;
} ThreadArgs;

void* copy_chunk(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    char buffer[4096];
    ssize_t bytes_read, bytes_written;
    off_t offset = args->start;

    while (offset < args->end) {
        lseek(args->src_fd, offset, SEEK_SET);
        bytes_read = read(args->src_fd, buffer, sizeof(buffer));
        lseek(args->dest_fd, offset, SEEK_SET);
        bytes_written = write(args->dest_fd, buffer, bytes_read);
        offset += bytes_read;
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <src> <dest> <threads>\n", argv[0]);
        exit(1);
    }

    int src_fd = open(argv[1], O_RDONLY);
    struct stat st;
    fstat(src_fd, &st);
    off_t file_size = st.st_size;

    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ftruncate(dest_fd, file_size);

    int
