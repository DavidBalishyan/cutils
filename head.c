#include "clibx.h"

#define DEFAULT_LINES 10

/*
 * head_file - print the first n lines from a file.
 * Uses getline() to support arbitrary line lengths.
 */
static void head_file(str path, int n) {
    FILE *fp = fopen(path, "r");
    if (!fp) {
        ERROR("cannot open '%s': %s", path, strerror(errno));
    }

    str line = NULL;
    size_t len = 0;
    int count = 0;

    while (getline(&line, &len, fp) != -1 && count < n) {
        printf("%s", line);
        count++;
    }

    free(line);
    fclose(fp);
}

/*
 * chead - prints the first N lines of a file or stdin.
 * Supports -nN and -n N option styles.
 */
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
        str line = NULL;
        size_t len = 0;
        int count = 0;

        while (getline(&line, &len, stdin) != -1 && count < n) {
            printf("%s", line);
            count++;
        }

        free(line);
        return EXIT_SUCCESS;
    }

    head_file(file, n);
    return EXIT_SUCCESS;
}
