#include "mini.c/array.h"
#include "mini.c/allocator.h"
#include "mini.c/mini_def.h"
#include <string.h>

#define MAGIC "887"

#define IS_MINI_ARRAY(header) (strncmp (header->magic, MAGIC, 3) == 0)

void *__mini_array_init (Mini_Allocator allocator, usize element_size,
                         usize initial_capacity, Mini_SourceLocation srcloc)
{
    if (initial_capacity == 0) {
        initial_capacity = MINI_ARRAY_DEFAULT_CAPACITY;
    }

    Mini_ArrayHeader_ *header = mini_allocator_alloc (
        allocator, sizeof (*header) + element_size * initial_capacity, srcloc);
    header->allocator    = allocator;
    header->capacity     = initial_capacity;
    header->count        = 0;
    header->element_size = element_size;
    memcpy (header->magic, MAGIC, strlen (MAGIC));
    void *array_start = (void *)(header + 1);
    memset (array_start, 0, element_size * initial_capacity);
    return array_start;
}

Mini_ArrayHeader_ *__mini_array_resize_if_needed (void **array, usize units)
{
    Mini_ArrayHeader_ *header = MINI_ARRAY_HDR (*array);
    MINI_ASSERT (IS_MINI_ARRAY (header), "This pointer is not a mini-array");

    usize needed = header->count + units;

    if (needed < header->capacity)
        return header;
    usize new_capacity = header->capacity * 2;

    while (new_capacity <= needed) {
        if (new_capacity == 0) {
            new_capacity = needed * 2;
            break;
        }
        new_capacity *= 2;
    }
    void *new_buffer = __mini_array_init (
        header->allocator, header->element_size, new_capacity, $M);
    Mini_ArrayHeader_ *new_header = MINI_ARRAY_HDR (new_buffer);
    new_header->count             = header->count;
    memcpy (new_buffer, *array, header->element_size * header->count);
    MINI_FREE (header->allocator, header);

    *array = new_buffer;

    return new_header;
}
