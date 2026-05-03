#include <stdio.h>
#include "clibx.h"

/*
 * cecho - minimal echo implementation.
 * Prints all provided command line arguments separated by spaces,
 * then terminates with a newline.
 */
int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (STREQ(argv[i], "--help") || STREQ(argv[i], "-h")) {
            printf("Usage: %s [args...]\n", argv[0]);
            printf("Print arguments to stdout separated by spaces.\n");
            return EXIT_SUCCESS;
        } else if (STREQ(argv[i], "--version") || STREQ(argv[i], "-v")) {
            printf("cecho (cutils) 1.0.0\n");
            return EXIT_SUCCESS;
        }
    }

    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        if (i < argc - 1) {
            putchar(' ');
        }
    }
    putchar('\n');
    return EXIT_SUCCESS;
}
