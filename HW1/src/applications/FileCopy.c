#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *srcFile, *dstFile;
    char buffer[1024];
    size_t bytesRead;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n",
                argv[0]);
        exit(1);
    }

    srcFile = fopen(argv[1], "rb");
    if (srcFile == NULL) {
        perror("Error opening source file");
        exit(1);
    }

    dstFile = fopen(argv[2], "wb");
    if (dstFile == NULL) {
        perror("Error opening destination file");
        exit(1);
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        fwrite(buffer, 1, bytesRead, dstFile);
    }

    fclose(srcFile);
    fclose(dstFile);

    return 0;
}
