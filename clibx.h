#ifndef CLIBX_H
#define CLIBX_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libgen.h>
#include <limits.h>

/*
 * CLIBX - Minimal C Utility Library
 * --------------------------------------
 * A lightweight header-only utility library providing:
 * - Array helpers
 * - Math macros
 * - Memory utilities
 * - Debug/logging tools
 * - Type utilities
 * - String helpers
 * --------------------------------------
 * Designed for convenience and zero dependencies.
 * */

//
// String type
//

/*
 * str (alias)
 * --------------------------------------
 * A simple alias for char* to improve readability when
 * working with strings.
 * --------------------------------------
 * Equivalent to: char*
 * */
typedef char *str;

//
// Array utilities
//

/*
 * ARRAY_SIZE
 * --------------------------------------
 * Computes the number of elements in a static array.
 * Only works for arrays, NOT pointers.
 * --------------------------------------
 * Complexity: O(1)
 * */
#define ARRAY_SIZE(arr) (sizeof arr / sizeof arr[0])

/*
 * print_int_array
 * --------------------------------------
 * Prints an integer array in [a, b, c] format.
 * --------------------------------------
 * Time complexity: O(n)
 * Space complexity: O(1)
 * */
static inline void print_int_array(const int *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]\n");
}

/*
 * print_double_array
 * --------------------------------------
 * Prints a double array in [a, b, c] format.
 * --------------------------------------
 * Time complexity: O(n)
 * Space complexity: O(1)
 * */
static inline void print_double_array(const double *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("%f", arr[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]\n");
}

/*
 * print_char_array
 * --------------------------------------
 * Prints a char array as ['a', 'b', 'c'].
 * --------------------------------------
 * Time complexity: O(n)
 * Space complexity: O(1)
 * */
static inline void print_char_array(const char *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("'%c'", arr[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]\n");
}

//
// Math utilities
//

/*
 * MIN / MAX
 * --------------------------------------
 * Returns the minimum / maximum of two values.
 * --------------------------------------
 * Complexity: O(1)
 * */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/*
 * CLAMP
 * --------------------------------------
 * Restricts a value x to the range [min, max].
 * --------------------------------------
 * Complexity: O(1)
 * */
#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

/*
 * ABS
 * --------------------------------------
 * Computes absolute value.
 * --------------------------------------
 * Complexity: O(1)
 * */
#define ABS(x) ((x) < 0 ? -(x) : (x))

/*
 * LERP (Linear Interpolation)
 * --------------------------------------
 * Interpolates between v0 and v1 using parameter t.
 * t = 0 -> v0, t = 1 -> v1
 * --------------------------------------
 * Complexity: O(1)
 * https://en.wikipedia.org/wiki/Linear_interpolation
 * */
#define LERP(v0, v1, t) ((v0) + (t) * ((v1) - (v0)))

/*
 * IS_POWER_OF_2
 * --------------------------------------
 * Checks if n is a power of 2.
 * --------------------------------------
 * Complexity: O(1)
 * */
#define IS_POWER_OF_2(n) ((n) && !((n) & ((n) - 1)))

/*
 * NEXT_POWER_OF_2
 * --------------------------------------
 * Computes the next power of 2 greater than n.
 * Uses floating-point math internally.
 * --------------------------------------
 * Complexity: O(1)
 * */
#define NEXT_POWER_OF_2(n) ((int)pow(2, ceil(log2((n) + 1))))

//
// Memory utilities
//

/*
 * NEW / NEW_ARRAY / NEW_ZEROED
 * --------------------------------------
 * Memory allocation helpers:
 * - NEW: allocate one object
 * - NEW_ARRAY: allocate array
 * - NEW_ZEROED: allocate zero-initialized object
 * --------------------------------------
 * Complexity: O(1)
 * */
#define NEW(type)              ((type*)malloc(sizeof(type)))
#define NEW_ARRAY(type, count) ((type*)malloc(sizeof(type) * (count)))
#define NEW_ZEROED(type)       ((type*)calloc(1, sizeof(type)))

/*
 * FREE
 * --------------------------------------
 * Frees memory and sets pointer to NULL.
 * Prevents dangling pointer bugs.
 * --------------------------------------
 * Complexity: O(1)
 * */
#define FREE(ptr) do { \
    free(ptr);         \
    ptr = NULL;        \
} while(0)

//
// Compiler-specific utilities (GCC/Clang)
//

#ifdef __GNUC__

/*
 * SWAP
 * --------------------------------------
 * Swaps two variables using type inference.
 * --------------------------------------
 * Complexity: O(1)
 * */
#define SWAP(a, b) do {          \
    __typeof__(a) _tmp = (a);    \
    (a) = (b);                   \
    (b) = _tmp;                  \
} while(0)

/*
 * Branch prediction hints
 * */
#define LIKELY(x)    __builtin_expect(!!(x), 1)
#define UNLIKELY(x)  __builtin_expect(!!(x), 0)

/*
 * UNUSED
 * --------------------------------------
 * Suppresses unused variable warnings.
 * */
#define UNUSED(x) (void)(x)

/*
 * Attributes
 * */
#define DEPRECATED   __attribute__((deprecated))
#define NODISCARD    __attribute__((warn_unused_result))

/*
 * Type utilities
 * */
#define TYPE_NAME(x) __typeof__(x)
#define TYPE_FUNC(x) _Generic((x), default: __PRETTY_FUNCTION__)

#else

/*
 * Portable SWAP fallback (memcpy-based)
 * */
#define SWAP(a, b) do {     \
    char _tmp[sizeof(a)];   \
    memcpy(_tmp,  &(a), sizeof(a)); \
    memcpy(&(a),  &(b), sizeof(a)); \
    memcpy(&(b),  _tmp, sizeof(a)); \
} while(0)

#define LIKELY(x)    (x)
#define UNLIKELY(x)  (x)
#define UNUSED(x)    (void)(x)
#define DEPRECATED
#define NODISCARD

#define TYPE_NAME(x) void
#define TYPE_FUNC(x) "<TYPE_FUNC unavailable: requires GCC/Clang>"

#endif

//
// Debug / logging
//

/*
 * LOG
 * --------------------------------------
 * Prints a formatted log message to stderr.
 * */
#define LOG(fmt, ...) \
    fprintf(stderr, "\033[1m\033[1;33m[LOG] \033[0m " fmt "\n", ##__VA_ARGS__)

/*
 * ERROR
 * --------------------------------------
 * Prints error message and exits program.
 * Includes file and line information.
 * */
#define ERROR(fmt, ...) do { \
    fprintf(stderr, "\033[1m\033[1;31m[ERROR] \033[0m %s:%d: " fmt "\n", \
            __FILE__, __LINE__, ##__VA_ARGS__); \
    exit(EXIT_FAILURE); \
} while(0)

/*
 * ASSERT
 * --------------------------------------
 * Runtime assertion with message.
 * */
#define ASSERT(cond, msg) do { \
    if (!(cond)) { ERROR("Assertion failed: %s", msg); } \
} while(0)

#define UNIMPLEMENTED() ERROR("not yet implemented")
#define UNREACHABLE()   ERROR("unreachable code reached")

//
// Loop helpers
//

/*
 * FOR / FOR_RANGE
 * --------------------------------------
 * Simplified loop macros.
 * --------------------------------------
 * FOR(i, n):         0 -> n-1
 * FOR_RANGE(i,a,b):  a -> b-1
 * */
#define FOR(i, n)                for (size_t i = 0; i < (n); i++)
#define FOR_RANGE(i, start, end) for (size_t i = (start); i < (end); i++)

//
// Bitwise operations
//

/*
 * BIT / SET_BIT / CLEAR_BIT / TOGGLE_BIT / CHECK_BIT
 * --------------------------------------
 * Bit manipulation macros.
 * --------------------------------------
 * Complexity: O(1)
 * */
#define BIT(x) (1ULL << (x))
#define SET_BIT(val, pos)   ((val) |= BIT(pos))
#define CLEAR_BIT(val, pos) ((val) &= ~BIT(pos))
#define TOGGLE_BIT(val, pos) ((val) ^= BIT(pos))
#define CHECK_BIT(val, pos) (((val) & BIT(pos)) != 0)

//
// Boolean helpers
//

#ifndef __cplusplus
    #ifndef bool
        #define clibx_bool  int
        #define clibx_true  1
        #define clibx_false 0
    #endif
#endif

/*
 * CLIBX_PRINT_BOOL
 * --------------------------------------
 * Prints boolean as "true" or "false".
 * */
#define CLIBX_PRINT_BOOL(b) ((b) == 1 ? printf("true\n") : printf("false\n"))

//
// String utilities
//

/*
 * STREQ
 * --------------------------------------
 * Compares two strings for equality.
 * */
#define STREQ(a, b) (strcmp((a), (b)) == 0)

/*
 * STR_EMPTY
 * --------------------------------------
 * Checks if string is empty.
 * */
#define STR_EMPTY(s) ((s)[0] == '\0')

/*
 * STR_STARTS_WITH
 * --------------------------------------
 * Checks if string starts with prefix.
 * */
#define STR_STARTS_WITH(s, p) (strncmp((s), (p), strlen(p)) == 0)

//
// Type introspection
//

/*
 * TYPE_STR
 * --------------------------------------
 * Returns string representation of type.
 * */
#define TYPE_STR(x) _Generic((x),   \
    int:     "int",                \
    long:    "long",               \
    float:   "float",              \
    double:  "double",             \
    char:    "char",               \
    default: "unknown by TYPE_STR")

/*
 * PRINT
 * --------------------------------------
 * Generic print macro for basic types.
 * */
#define PRINT(x) _Generic((x),        \
    int:     printf("%d\n",  (x)),    \
    long:    printf("%ld\n", (x)),    \
    float:   printf("%f\n",  (x)),    \
    double:  printf("%f\n",  (x)),    \
    char:    printf("%c\n",  (x)),    \
    char*:   printf("%s\n",  (x)),    \
    default: printf("<unknown type>\n"))

//
// I/O utilities
//

/*
 * read_line
 * --------------------------------------
 * Reads a line from stdin safely.
 * Removes trailing newline if present.
 * --------------------------------------
 * Time complexity: O(n)
 * */
static inline void read_line(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
    }
}

//
// Dynamic array (Vec)
//

typedef struct {
    str *data;
    size_t length;
    size_t capacity;
} str_vec;

/*
 * vec_init
 * --------------------------------------
 * Initialize an empty string vector.
 * */
static inline str_vec vec_init(void) {
    return (str_vec){ .data = NULL, .length = 0, .capacity = 0 };
}

/*
 * vec_push
 * --------------------------------------
 * Append a string to the vector.
 * */
static inline void vec_push(str_vec *vec, str value) {
    if (vec->length >= vec->capacity) {
        size_t new_cap = vec->capacity == 0 ? 8 : vec->capacity * 2;
        vec->data = realloc(vec->data, sizeof(str) * new_cap);
        ASSERT(vec->data != NULL, "vec_push: realloc failed");
        vec->capacity = new_cap;
    }
    vec->data[vec->length++] = value;
}

/*
 * vec_free
 * --------------------------------------
 * Free the vector's internal data.
 * Does NOT free individual strings.
 * */
static inline void vec_free(str_vec *vec) {
    FREE(vec->data);
    vec->length = 0;
    vec->capacity = 0;
}

//
// String utilities
//

/*
 * strtrim
 * --------------------------------------
 * Returns a newly allocated trimmed string (leading/trailing whitespace removed).
 * Caller must free the result.
 * --------------------------------------
 * Time complexity: O(n)
 * */
static inline str strtrim(str s) {
    if (!s || *s == '\0') return strdup("");

    str copy = strdup(s);
    str start = copy;
    while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r') start++;
    if (*start == '\0') { free(copy); return strdup(""); }

    str end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
        end--;
    *(end + 1) = '\0';

    str result = strdup(start);
    free(copy);
    return result;
}

/*
 * strsplit
 * --------------------------------------
 * Splits a string by delimiter into a vec.
 * Caller must free vec and individual strings.
 * --------------------------------------
 * Time complexity: O(n)
 * */
static inline str_vec strsplit(str input, char delim) {
    str_vec result = vec_init();
    char *copy = strdup(input);
    char delim_str[2] = {delim, '\0'};
    char *token = strtok(copy, delim_str);

    while (token != NULL) {
        vec_push(&result, strdup(token));
        token = strtok(NULL, delim_str);
    }

    free(copy);
    return result;
}

/*
 * strjoin
 * --------------------------------------
 * Joins an array of strings with a separator.
 * Returns a newly allocated string. Caller must free.
 * --------------------------------------
 * Time complexity: O(n)
 * */
static inline str strjoin(str *arr, size_t len, str sep) {
    if (len == 0) return strdup("");

    size_t total_len = 0;
    for (size_t i = 0; i < len; i++) {
        total_len += strlen(arr[i]);
        if (i < len - 1) total_len += strlen(sep);
    }

    str result = NEW_ARRAY(char, total_len + 1);
    ASSERT(result != NULL, "strjoin: malloc failed");

    result[0] = '\0';
    for (size_t i = 0; i < len; i++) {
        strcat(result, arr[i]);
        if (i < len - 1) strcat(result, sep);
    }

    return result;
}

/*
 * str_contains
 * --------------------------------------
 * Checks if haystack contains needle.
 * */
#define STR_CONTAINS(haystack, needle) (strstr((haystack), (needle)) != NULL)

/*
 * str_to_lower
 * --------------------------------------
 * Converts string to lowercase in place. Returns same pointer.
 * */
static inline str str_to_lower(str s) {
    for (size_t i = 0; s[i]; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] + 32;
    }
    return s;
}

/*
 * str_to_upper
 * --------------------------------------
 * Converts string to uppercase in place. Returns same pointer.
 * */
static inline str str_to_upper(str s) {
    for (size_t i = 0; s[i]; i++) {
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = s[i] - 32;
    }
    return s;
}

//
// Path utilities
//

/*
 * path_basename
 * --------------------------------------
 * Returns the filename component of a path.
 * */
static inline str path_basename(str path) {
    char *copy = strdup(path);
    str result = strdup(basename(copy));
    free(copy);
    return result;
}

/*
 * path_dirname
 * --------------------------------------
 * Returns the directory component of a path.
 * */
static inline str path_dirname(str path) {
    char *copy = strdup(path);
    str result = strdup(dirname(copy));
    free(copy);
    return result;
}

/*
 * path_extension
 * --------------------------------------
 * Returns the file extension (without dot), or empty string.
 * */
static inline str path_extension(str path) {
    str base = path_basename(path);
    str dot = strrchr(base, '.');
    str ext = dot ? strdup(dot + 1) : strdup("");
    free(base);
    return ext;
}

/*
 * path_join
 * --------------------------------------
 * Joins two path components with '/'.
 * Returns a newly allocated string. Caller must free.
 * */
static inline str path_join(str a, str b) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    size_t sep = (len_a > 0 && a[len_a - 1] != '/') ? 1 : 0;

    str result = NEW_ARRAY(char, len_a + sep + len_b + 1);
    ASSERT(result != NULL, "path_join: malloc failed");

    sprintf(result, "%s%s%s", a, sep ? "/" : "", b);
    return result;
}

/*
 * path_exists
 * --------------------------------------
 * Checks if a path exists on disk.
 * */
static inline clibx_bool path_exists(str path) {
    return access(path, F_OK) == 0;
}

/*
 * path_is_dir
 * --------------------------------------
 * Checks if a path is a directory.
 * */
static inline clibx_bool path_is_dir(str path) {
    struct stat st;
    return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

/*
 * path_is_file
 * --------------------------------------
 * Checks if a path is a regular file.
 * */
static inline clibx_bool path_is_file(str path) {
    struct stat st;
    return (stat(path, &st) == 0 && S_ISREG(st.st_mode));
}

/*
 * path_file_size
 * --------------------------------------
 * Returns file size in bytes, or -1 on error.
 * */
static inline long path_file_size(str path) {
    struct stat st;
    if (stat(path, &st) != 0) return -1;
    return (long)st.st_size;
}

//
// Hash Map
//

#define CLIBX_HASHMAP_DEFAULT_CAPACITY 64

typedef struct clibx_hashmap_entry {
    str key;
    str value;
    struct clibx_hashmap_entry *next;
} clibx_hashmap_entry;

typedef struct {
    clibx_hashmap_entry **buckets;
    size_t capacity;
    size_t count;
} clibx_hashmap;

/*
 * hashmap_hash
 * --------------------------------------
 * Simple DJB2 hash function.
 * */
static inline unsigned long hashmap_hash(str key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

/*
 * hashmap_init
 * --------------------------------------
 * Create a new empty hashmap.
 * */
static inline clibx_hashmap hashmap_init(void) {
    clibx_hashmap map;
    map.capacity = CLIBX_HASHMAP_DEFAULT_CAPACITY;
    map.count = 0;
    map.buckets = NEW_ARRAY(clibx_hashmap_entry*, map.capacity);
    memset(map.buckets, 0, sizeof(clibx_hashmap_entry*) * map.capacity);
    return map;
}

/*
 * hashmap_put
 * --------------------------------------
 * Insert or update a key-value pair.
 * */
static inline void hashmap_put(clibx_hashmap *map, str key, str value) {
    unsigned long hash = hashmap_hash(key) % map->capacity;
    clibx_hashmap_entry *entry = map->buckets[hash];

    while (entry != NULL) {
        if (STREQ(entry->key, key)) {
            free(entry->value);
            entry->value = strdup(value);
            return;
        }
        entry = entry->next;
    }

    clibx_hashmap_entry *new_entry = NEW_ZEROED(clibx_hashmap_entry);
    new_entry->key = strdup(key);
    new_entry->value = strdup(value);
    new_entry->next = map->buckets[hash];
    map->buckets[hash] = new_entry;
    map->count++;
}

/*
 * hashmap_get
 * --------------------------------------
 * Get value by key. Returns NULL if not found.
 * */
static inline str hashmap_get(clibx_hashmap *map, str key) {
    unsigned long hash = hashmap_hash(key) % map->capacity;
    clibx_hashmap_entry *entry = map->buckets[hash];

    while (entry != NULL) {
        if (STREQ(entry->key, key))
            return entry->value;
        entry = entry->next;
    }
    return NULL;
}

/*
 * hashmap_contains
 * --------------------------------------
 * Check if key exists in hashmap.
 * */
static inline clibx_bool hashmap_contains(clibx_hashmap *map, str key) {
    return hashmap_get(map, key) != NULL;
}

/*
 * hashmap_free
 * --------------------------------------
 * Free all memory used by the hashmap.
 * */
static inline void hashmap_free(clibx_hashmap *map) {
    for (size_t i = 0; i < map->capacity; i++) {
        clibx_hashmap_entry *entry = map->buckets[i];
        while (entry != NULL) {
            clibx_hashmap_entry *next = entry->next;
            free(entry->key);
            free(entry->value);
            free(entry);
            entry = next;
        }
    }
    FREE(map->buckets);
    map->count = 0;
    map->capacity = 0;
}

#endif /* CLIBX_H */
