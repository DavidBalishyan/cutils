#include "clibx.h"

typedef struct {
    long lines;
    long words;
    long bytes;
} wc_result;

/*
 * count_stream - count lines, words, and bytes from a FILE stream.
 * Uses a small state machine to detect word boundaries.
 */
static wc_result count_stream(FILE *fp) {
    wc_result result = { 0, 0, 0 };
    int c;
    clibx_bool in_word = clibx_false;

    while ((c = fgetc(fp)) != EOF) {
        result.bytes++;
        if (c == '\n') result.lines++;

        if (c == ' ' || c == '\t' || c == '\n') {
            in_word = clibx_false;
        } else if (!in_word) {
            in_word = clibx_true;
            result.words++;
        }
    }

    return result;
}

static void wc_file(str path, wc_result *total) {
    FILE *fp = fopen(path, "r");
    if (!fp) {
        ERROR("cannot open '%s': %s", path, strerror(errno));
    }

    wc_result result = count_stream(fp);
    fclose(fp);

    printf("%8ld %8ld %8ld %s\n", result.lines, result.words, result.bytes, path);

    total->lines += result.lines;
    total->words += result.words;
    total->bytes += result.bytes;
}

/*
 * cwc - count lines, words, and bytes. Reads stdin when no files are given.
 */
int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (STREQ(argv[i], "--help") || STREQ(argv[i], "-h")) {
            printf("Usage: %s [files...]\n", argv[0]);
            printf("Count lines, words, and bytes in files or stdin.\n");
            return EXIT_SUCCESS;
        } else if (STREQ(argv[i], "--version") || STREQ(argv[i], "-v")) {
            printf("cwc (cutils) 1.0.0\n");
            return EXIT_SUCCESS;
        }
    }

    if (argc < 2) {
        wc_result result = count_stream(stdin);
        printf("%8ld %8ld %8ld\n", result.lines, result.words, result.bytes);
        return EXIT_SUCCESS;
    }

    wc_result total = { 0, 0, 0 };
    FOR_RANGE(i, 1, argc) {
        wc_file(argv[i], &total);
    }

    if (argc > 2) {
        printf("%8ld %8ld %8ld total\n", total.lines, total.words, total.bytes);
    }

    return EXIT_SUCCESS;
}
