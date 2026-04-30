#include "clibx.h"

static int cmp_str(const void *a, const void *b) {
    return strcmp(*(const str *)a, *(const str *)b);
}

int main(int argc, char **argv) {
    str_vec lines = vec_init();
    clibx_bool reverse = clibx_false;
    str file = NULL;

    FOR_RANGE(i, 1, argc) {
        if (STREQ(argv[i], "-r") || STREQ(argv[i], "--reverse")) {
            reverse = clibx_true;
        } else if (argv[i][0] != '-') {
            file = argv[i];
        }
    }

    FILE *fp = file ? fopen(file, "r") : stdin;
    if (!fp) {
        ERROR("cannot open '%s': %s", file, strerror(errno));
    }

    str line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != -1) {
        vec_push(&lines, strdup(line));
    }

    free(line);
    if (fp != stdin) fclose(fp);

    qsort(lines.data, lines.length, sizeof(str), cmp_str);

    if (reverse) {
        for (long i = lines.length - 1; i >= 0; i--) {
            printf("%s", lines.data[i]);
        }
    } else {
        FOR(i, lines.length) {
            printf("%s", lines.data[i]);
        }
    }

    FOR(i, lines.length) {
        free(lines.data[i]);
    }
    vec_free(&lines);

    return EXIT_SUCCESS;
}
