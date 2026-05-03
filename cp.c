#include "clibx.h"

#define BUF_SIZE 8192

/*
 * copy_file - copy a binary file from src to dest.
 * Uses buffered reads and writes to handle large files efficiently.
 */
static void copy_file(str src, str dest) {
    FILE *in = fopen(src, "rb");
    if (!in) {
        ERROR("cannot open '%s': %s", src, strerror(errno));
    }

    FILE *out = fopen(dest, "wb");
    if (!out) {
        fclose(in);
        ERROR("cannot create '%s': %s", dest, strerror(errno));
    }

    char buf[BUF_SIZE];
    size_t bytes;
    while ((bytes = fread(buf, 1, BUF_SIZE, in)) > 0) {
        if (fwrite(buf, 1, bytes, out) != bytes) {
            ERROR("write to '%s' failed: %s", dest, strerror(errno));
        }
    }

    fclose(in);
    fclose(out);
}

/*
 * ccp - simple file copy tool.
 * Accepts a source and destination path. If the destination is a directory,
 * the source file is copied into that directory using its basename.
 */
int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (STREQ(argv[i], "--help") || STREQ(argv[i], "-h")) {
            printf("Usage: %s <source> <destination>\n", argv[0]);
            printf("Copy a file from source to destination.\n");
            printf("If destination is a directory, the file is copied into it.\n");
            return EXIT_SUCCESS;
        } else if (STREQ(argv[i], "--version") || STREQ(argv[i], "-v")) {
            printf("ccp (cutils) 1.0.0\n");
            return EXIT_SUCCESS;
        }
    }

    if (argc < 3) {
        ERROR("usage: %s <source> <destination>", argv[0]);
    }

    str src = argv[1];
    str dest = argv[2];

    if (!path_exists(src)) {
        ERROR("source '%s' does not exist", src);
    }

    if (path_is_dir(dest)) {
        str base = path_basename(src);
        str full_dest = path_join(dest, base);
        copy_file(src, full_dest);
        free(base);
        free(full_dest);
    } else {
        copy_file(src, dest);
    }

    return EXIT_SUCCESS;
}
