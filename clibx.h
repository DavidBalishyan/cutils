#ifndef CLIBX_H
#define CLIBX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Array utilities

#define ARRAY_SIZE(arr) (sizeof arr / sizeof arr[0])

static inline void print_int_array(const int *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]\n");
}

static inline void print_double_array(const double *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("%f", arr[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]\n");
}

static inline void print_char_array(const char *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("'%c'", arr[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]\n");
}

// Math 

#define MIN(a, b)            ((a) < (b) ? (a) : (b))
#define MAX(a, b)            ((a) > (b) ? (a) : (b))
#define CLAMP(x, min, max)   ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#define ABS(x)               ((x) < 0 ? -(x) : (x))
#define LERP(v0, v1, t)      ((v0) + (t) * ((v1) - (v0)))
#define IS_POWER_OF_2(n)     ((n) && !((n) & ((n) - 1)))
#define NEXT_POWER_OF_2(n)   ((int)pow(2, ceil(log2((n) + 1))))

// Memory 

#define NEW(type)              ((type*)malloc(sizeof(type)))
#define NEW_ARRAY(type, count) ((type*)malloc(sizeof(type) * (count)))
#define NEW_ZEROED(type)       ((type*)calloc(1, sizeof(type)))

#define FREE(ptr) do { \
    free(ptr);         \
    ptr = NULL;        \
} while(0)

// GCC/Clang-specific 

#ifdef __GNUC__

#define SWAP(a, b) do {          \
    __typeof__(a) _tmp = (a);    \
    (a) = (b);                   \
    (b) = _tmp;                  \
} while(0)

#define LIKELY(x)    __builtin_expect(!!(x), 1)
#define UNLIKELY(x)  __builtin_expect(!!(x), 0)

#define UNUSED(x)    (void)(x)

#define DEPRECATED   __attribute__((deprecated))
#define NODISCARD    __attribute__((warn_unused_result))

#define TYPE_NAME(x) __typeof__(x)
#define TYPE_FUNC(x) _Generic((x), default: __PRETTY_FUNCTION__)

#else

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

#endif /* __GNUC__ */

// Debug / logging 

#define LOG(fmt, ...) \
    fprintf(stderr, "\033[1m\033[1;33m[LOG] \033[0m " fmt "\n", ##__VA_ARGS__)

#define ERROR(fmt, ...) do { \
    fprintf(stderr, "\033[1m\033[1;31m[ERROR] \033[0m %s:%d: " fmt "\n", \
            __FILE__, __LINE__, ##__VA_ARGS__); \
    exit(EXIT_FAILURE); \
} while(0)

#define ASSERT(cond, msg) do { \
    if (!(cond)) { ERROR("Assertion failed: %s", msg); } \
} while(0)

#define UNIMPLEMENTED()  ERROR("not yet implemented")
#define UNREACHABLE()    ERROR("unreachable code reached")

// Loop helpers 

#define FOR(i, n)                for (size_t i = 0; i < (n); i++)
#define FOR_RANGE(i, start, end) for (size_t i = (start); i < (end); i++)

// Booleans 

#ifndef __cplusplus
    #ifndef bool
        #define clibx_bool  int
        #define clibx_true  1
        #define clibx_false 0
    #endif
#endif

#define CLIBX_PRINT_BOOL(b) ((b) == 1 ? printf("true\n") : printf("false\n"))

// String utilities

#define STREQ(a, b)           (strcmp((a), (b)) == 0)
#define STR_EMPTY(s)          ((s)[0] == '\0')
#define STR_STARTS_WITH(s, p) (strncmp((s), (p), strlen(p)) == 0)

// Type introspection

#define TYPE_STR(x) _Generic((x),   \
    int:     "int",                  \
    long:    "long",                 \
    float:   "float",                \
    double:  "double",               \
    char:    "char",                 \
    default: "unknown by TYPE_STR")

#define PRINT(x) _Generic((x),        \
    int:     printf("%d\n",  (x)),    \
    long:    printf("%ld\n", (x)),    \
    float:   printf("%f\n",  (x)),    \
    double:  printf("%f\n",  (x)),    \
    char:    printf("%c\n",  (x)),    \
    char*:   printf("%s\n",  (x)),    \
    default: printf("<unknown type>\n"))

// I/O 

static inline void read_line(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
    }
}

#endif /* CLIBX_H */