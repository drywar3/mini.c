#ifndef MINI_DEF_H
#define MINI_DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef size_t usize;
typedef ptrdiff_t isize;

#define MINI_PANIC(msg, ...)                                                   \
    do {                                                                       \
        fprintf (stderr, "[PANIC]: %s:%d: " msg "\n", __FILE__, __LINE__,      \
                 ##__VA_ARGS__);                                               \
        abort ();                                                              \
    } while (0)

#define MINI_UNREACHABLE(msg, ...)                                             \
    do {                                                                       \
        fprintf (stderr, "[UNREACHABLE]: %s:%d: " msg "\n", __FILE__,          \
                 __LINE__, ##__VA_ARGS__);                                     \
        abort ();                                                              \
    } while (0)

#define MINI_ASSERT(cond, msg, ...)                                            \
    do {                                                                       \
        if (!(cond)) {                                                         \
            fprintf (stderr,                                                   \
                     "[ASSERTION (" #cond ") FAILED]: %s:%d: " msg "\n",       \
                     __FILE__, __LINE__, ##__VA_ARGS__);                       \
            abort ();                                                          \
        }                                                                      \
    } while (0)

typedef struct
{
    const char *filename;
    usize line;
} Mini_SourceLocation;

#define MINI_SOURCE_LOCATION                                                   \
    (Mini_SourceLocation)                                                      \
    {                                                                          \
        __FILE__, __LINE__                                                     \
    }

#endif // MINI_DEF_H
