#include "clibx.h"

/*
 * cmv - minimal move/rename implementation.
 * Uses the POSIX rename() syscall to rename or relocate a file.
 */
int main(int argc, char **argv) {
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
