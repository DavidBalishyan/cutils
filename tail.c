#include "clibx.h"

#define DEFAULT_LINES 10

static void tail_file(str path, int n) {
    str_vec lines = vec_init();
    FILE *fp = fopen(path, "r");
    if (!fp) {
        ERROR("cannot open '%s': %s", path, strerror(errno));
    }

    str line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != -1) {
        vec_push(&lines, strdup(line));
    }

    free(line);
    fclose(fp);

    size_t start = lines.length > (size_t)n ? lines.length - n : 0;
    FOR_RANGE(i, start, lines.length) {
        printf("%s", lines.data[i]);
        free(lines.data[i]);
    }

    vec_free(&lines);
}

int main(int argc, char **argv) {
    int n = DEFAULT_LINES;
    str file = NULL;

    FOR_RANGE(i, 1, argc) {
        if (STREQ(argv[i], "-n")) {
            if (i + 1 < argc) {
                n = atoi(argv[++i]);
            } else {
                ERROR("-n requires a number argument");
            }
        } else if (STR_STARTS_WITH(argv[i], "-n")) {
            n = atoi(argv[i] + 2);
        } else if (argv[i][0] != '-') {
            file = argv[i];
        }
    }

    if (!file) {
        str_vec lines = vec_init();
        str line = NULL;
        size_t len = 0;

        while (getline(&line, &len, stdin) != -1) {
            vec_push(&lines, strdup(line));
        }
        free(line);

        size_t start = lines.length > (size_t)n ? lines.length - n : 0;
        FOR_RANGE(i, start, lines.length) {
            printf("%s", lines.data[i]);
            free(lines.data[i]);
        }
        vec_free(&lines);

        return EXIT_SUCCESS;
    }

    tail_file(file, n);

    return EXIT_SUCCESS;
}
