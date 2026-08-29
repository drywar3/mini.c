#ifndef MINI_ARRAY_H
#define MINI_ARRAY_H

#include "mini.c/allocator.h"
#include "mini_def.h"

#define MINI_ARRAY(T) T *
#define MINI_ARRAY_INIT(allocator, T)                                          \
    __mini_array_init (allocator, sizeof (T), MINI_ARRAY_DEFAULT_CAPACITY, $M)

#ifndef MINI_ARRAY_DEFAULT_CAPACITY
#define MINI_ARRAY_DEFAULT_CAPACITY 8
#endif

#define MINI_ARRAY_HDR(array) (((Mini_ArrayHeader_ *)array) - 1)

typedef struct
{
    char magic[3];
    Mini_Allocator allocator;
    usize element_size;
    usize count;
    usize capacity;
} Mini_ArrayHeader_;

void *__mini_array_init (Mini_Allocator allocator, usize element_size,
                         usize initial_capacity, Mini_SourceLocation);
Mini_ArrayHeader_ *__mini_array_resize_if_needed (void **array, usize units);

#define MINI_ARRAY_APPEND(array, item)                                         \
    do {                                                                       \
        Mini_ArrayHeader_ *header =                                            \
            __mini_array_resize_if_needed ((void **)&(array), 1);              \
        array[header->count++] = item;                                         \
    } while (0)

#endif // MINI_ARRAY_H
