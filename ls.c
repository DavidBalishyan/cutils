#include "clibx.h"
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

/*
 * print_permissions - convert a mode bitmask into a human-readable
 * permission string like "-rw-r--r--".
 */
static void print_permissions(mode_t mode) {
    putchar(S_ISDIR(mode) ? 'd' : '-');
    putchar(mode & S_IRUSR ? 'r' : '-');
    putchar(mode & S_IWUSR ? 'w' : '-');
    putchar(mode & S_IXUSR ? 'x' : '-');
    putchar(mode & S_IRGRP ? 'r' : '-');
    putchar(mode & S_IWGRP ? 'w' : '-');
    putchar(mode & S_IXGRP ? 'x' : '-');
    putchar(mode & S_IROTH ? 'r' : '-');
    putchar(mode & S_IWOTH ? 'w' : '-');
    putchar(mode & S_IXOTH ? 'x' : '-');
    putchar(' ');
}

/*
 * format_size - pretty-print file sizes in a compact unit form.
 */
static str format_size(off_t size) {
    static char buf[32];
    if (size < 1024) {
        sprintf(buf, "%ld", (long)size);
    } else if (size < 1024 * 1024) {
        sprintf(buf, "%.1fK", (double)size / 1024);
    } else if (size < 1024 * 1024 * 1024) {
        sprintf(buf, "%.1fM", (double)size / (1024 * 1024));
    } else {
        sprintf(buf, "%.1fG", (double)size / (1024 * 1024 * 1024));
    }
    return buf;
}

/*
 * list_file - output one directory entry in either short or long format.
 */
static void list_file(str path, str name, clibx_bool long_format) {
    struct stat st;
    if (lstat(path, &st) != 0) {
        ERROR("cannot stat '%s': %s", name, strerror(errno));
    }

    if (!long_format) {
        printf("%s\n", name);
        return;
    }

    print_permissions(st.st_mode);
    printf("%ld ", (long)st.st_nlink);

    struct passwd *pw = getpwuid(st.st_uid);
    printf("%-8s ", pw ? pw->pw_name : "?");

    struct group *gr = getgrgid(st.st_gid);
    printf("%-8s ", gr ? gr->gr_name : "?");

    printf("%-6s ", format_size(st.st_size));

    char timebuf[64];
    struct tm *tm = localtime(&st.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm);
    printf("%s ", timebuf);

    printf("%s\n", name);
}

static int cmp_str(const void *a, const void *b) {
    return strcmp(*(const str *)a, *(const str *)b);
}

/*
 * cls - a simplified ls implementation.
 * Supports -l, -a, -la, and --long-all.
 */
int main(int argc, char **argv) {
    clibx_bool long_format = clibx_false;
    clibx_bool show_hidden = clibx_false;
    str dir = ".";

    FOR(i, argc) {
        if (STREQ(argv[i], "-l") || STREQ(argv[i], "--long")) {
            long_format = clibx_true;
        } else if (STREQ(argv[i], "-a") || STREQ(argv[i], "--all")) {
            show_hidden = clibx_true;
        } else if (STREQ(argv[i], "-la") || STREQ(argv[i], "-al") ||
                   STREQ(argv[i], "--long-all")) {
            long_format = clibx_true;
            show_hidden = clibx_true;
        } else if (argv[i][0] != '-') {
            dir = argv[i];
        }
    }

    DIR *dp = opendir(dir);
    if (!dp) {
        ERROR("cannot open directory '%s': %s", dir, strerror(errno));
    }

    str_vec entries = vec_init();
    struct dirent *ep;

    while ((ep = readdir(dp)) != NULL) {
        if (!show_hidden && ep->d_name[0] == '.') continue;
        vec_push(&entries, strdup(ep->d_name));
    }
    closedir(dp);

    qsort(entries.data, entries.length, sizeof(str), cmp_str);

    if (long_format) {
        printf("total %zu\n", entries.length);
    }

    FOR(i, entries.length) {
        str path = path_join(dir, entries.data[i]);
        list_file(path, entries.data[i], long_format);
        free(path);
    }

    FOR(i, entries.length) {
        free(entries.data[i]);
    }
    vec_free(&entries);

    return EXIT_SUCCESS;
}
