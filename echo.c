#include <stdio.h>

/*
 * cecho - minimal echo implementation.
 * Prints all provided command line arguments separated by spaces,
 * then terminates with a newline.
 */
int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        if (i < argc - 1) {
            putchar(' ');
        }
    }
    putchar('\n');
    return 0;
}
