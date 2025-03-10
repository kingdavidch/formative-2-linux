#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <src> <dest>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    FILE *dest = fopen(argv[2], "wb");
    char buffer[4096];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(src);
    fclose(dest);
    return 0;
}
