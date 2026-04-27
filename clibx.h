#ifndef CLIBX_H
#define CLIBX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

#endif /* CLIBX_H */
