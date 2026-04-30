#include "clibx.h"

#define BUF_SIZE 8192

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

int main(int argc, char **argv) {
    if (argc < 3) {
        ERROR("usage: ccp <source> <destination>");
    }

    str src = argv[1];
    str dest = argv[2];

    if (!path_exists(src)) {
        ERROR("source '%s' does not exist", src);
    }

    if (path_is_dir(src) && path_is_dir(dest)) {
        str base = path_basename(src);
        str full_dest = path_join(dest, base);
        copy_file(src, full_dest);
        free(base);
        free(full_dest);
    } else if (path_is_dir(dest)) {
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
