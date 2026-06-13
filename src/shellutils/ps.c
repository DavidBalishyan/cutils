#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include "clibx.h"

/*
 * is_number - determine whether a string contains only digits.
 * Used to filter the numeric entries under /proc so only PIDs are listed.
 */
int is_number(const char *str) {
    while (*str) {
        if (!isdigit((unsigned char)*str)) return EXIT_SUCCESS;
        str++;
    }
    return EXIT_FAILURE;
}

/*
 * cps - a simple process listing tool for Linux.
 * It reads /proc and prints the PID and command line for each process.
 */
int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (STREQ(argv[i], "--help") || STREQ(argv[i], "-h")) {
            printf("Usage: %s\n", argv[0]);
            printf("List running processes from /proc (Linux only).\n");
            return EXIT_SUCCESS;
        } else if (STREQ(argv[i], "--version") || STREQ(argv[i], "-v")) {
            printf("cps (cutils) 1.0.0\n");
            return EXIT_SUCCESS;
        }
    }

    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("Failed to open /proc");
        return EXIT_FAILURE;
    }

    printf("%5s %s\n", "PID", "CMD");
    struct dirent *entry;

    while ((entry = readdir(proc)) != NULL) {
        if (!is_number(entry->d_name)) continue;

        char cmdline_path[256];
        FILE *cmdline_file;
        char cmdline[1024];

        snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%s/cmdline", entry->d_name);
        cmdline_file = fopen(cmdline_path, "r");
        if (!cmdline_file) continue;

        if (fgets(cmdline, sizeof(cmdline), cmdline_file)) {
            for (size_t i = 0; i < strlen(cmdline); i++) {
                if (cmdline[i] == '\0') {
                    cmdline[i] = ' ';
                }
            }
            printf("%5s %s\n", entry->d_name, cmdline);
        }
        fclose(cmdline_file);
    }

    closedir(proc);
    return EXIT_SUCCESS;
}