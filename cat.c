#include <stdio.h>
#include "clibx.h"

/*
 * ccat - a tiny cat implementation.
 * Reads the contents of a file one character at a time and writes them
 * directly to stdout.
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <file-path>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        ERROR("File reading error");
    }

    /* Keep reading until EOF. fgetc returns int to distinguish EOF. */
    while (clibx_true) {
        int c = fgetc(fp);
        if (c == EOF) {
            break;
        }
        putchar(c);
    }

    /* Provide a final newline for nicer terminal output. */
    putchar('\n');
    fclose(fp);
    return 0;
}
