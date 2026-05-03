#include <stdio.h>
#include "clibx.h"

/*
 * ccat - a tiny cat implementation.
 * Reads the contents of a file one character at a time and writes them
 * directly to stdout.
 */
int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (STREQ(argv[i], "--help") || STREQ(argv[i], "-h")) {
            printf("Usage: %s <file>\n", argv[0]);
            printf("Print the contents of a file to stdout.\n");
            return EXIT_SUCCESS;
        } else if (STREQ(argv[i], "--version") || STREQ(argv[i], "-v")) {
            printf("ccat (cutils) 1.0.0\n");
            return EXIT_SUCCESS;
        }
		
    }

    if (argc < 2) {
        ERROR("Usage: %s <file-path>", argv[0]);
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        ERROR("File reading error");
        return EXIT_FAILURE;
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
    return EXIT_SUCCESS;
}
