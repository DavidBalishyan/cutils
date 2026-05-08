#include "clibx.h"
#include <errno.h>

/*
 * cmv - minimal move/rename implementation.
 * Uses the POSIX rename() syscall to rename or relocate a file.
 */
int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (STREQ(argv[i], "--help") || STREQ(argv[i], "-h")) {
            printf("Usage: %s <source> <destination>\n", argv[0]);
            printf("Move or rename a file from source to destination.\n");
            return EXIT_SUCCESS;
        } else if (STREQ(argv[i], "--version") || STREQ(argv[i], "-v")) {
            printf("cmv (cutils) 1.0.0\n");
            return EXIT_SUCCESS;
        }
    }

    if (argc < 3) {
        ERROR("usage: cmv <source> <destination>");
    }

    str src = argv[1];
    str dest = argv[2];

    if (!path_exists(src)) {
        ERROR("source '%s' does not exist", src);
    }

    if (rename(src, dest) != 0) {
        ERROR("cannot move '%s' to '%s': %s", src, dest, strerror(errno));
    }

    return EXIT_SUCCESS;
}
