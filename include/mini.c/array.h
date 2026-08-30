#ifndef MINI_ARRAY_H
#define MINI_ARRAY_H

#include "mini.c/allocator.h"
#include "mini_def.h"

#define MINI_ARRAY(T) T *
#define MINI_ARRAY_INIT(allocator, T)                                          \
    __mini_array_init (allocator, sizeof (T), MINI_ARRAY_DEFAULT_CAPACITY,     \
                       MINI_SOURCE_LOCATION)

#ifndef MINI_ARRAY_DEFAULT_CAPACITY
#define MINI_ARRAY_DEFAULT_CAPACITY 8
#endif

#define MINI_ARRAY_HDR(array) (((Mini_ArrayHeader_ *)(array)) - 1)

typedef void (*Mini_ArrayElementDtor) (void *element);

typedef struct
{
    char magic[3];
    Mini_Allocator allocator;
    usize element_size;
    usize count;
    usize capacity;
    Mini_ArrayElementDtor dtor;
} Mini_ArrayHeader_;

void *__mini_array_init (Mini_Allocator allocator, usize element_size,
                         usize initial_capacity, Mini_SourceLocation);
Mini_ArrayHeader_ *__mini_array_resize_if_needed (void **array, usize units);

void mini_array_set_dtor (void *array, Mini_ArrayElementDtor dtor);
void mini_array_destroy (void *array);
usize mini_array_count (void *array);

#define mini_array_append(array, item)                                         \
    do {                                                                       \
        Mini_ArrayHeader_ *header_ =                                           \
            __mini_array_resize_if_needed ((void **)&(array), 1);              \
        (array)[header_->count] = (item);                                      \
        header_->count += 1;                                                   \
    } while (0)

#define mini_array_insert(array, index, item)                                  \
    do {                                                                       \
        Mini_ArrayHeader_ *header_ =                                           \
            __mini_array_resize_if_needed ((void **)&(array), 1);              \
        usize idx_ = (index);                                                  \
        if (idx_ < header_->count) {                                           \
            memmove (&(array)[idx_ + 1], &(array)[idx_],                       \
                     (header_->count - idx_) * sizeof (*(array)));             \
        }                                                                      \
        (array)[idx_] = (item);                                                \
        header_->count += 1;                                                   \
    } while (0)

#define mini_array_insert_range(array, index, items, item_count)               \
    do {                                                                       \
        usize count_ = (usize)(item_count);                                    \
        if (count_ > 0) {                                                      \
            Mini_ArrayHeader_ *header_ =                                       \
                __mini_array_resize_if_needed ((void **)&(array), count_);     \
            usize idx_ = (usize)(index);                                       \
            if (idx_ < header_->count) {                                       \
                memmove (&(array)[idx_ + count_], &(array)[idx_],              \
                         (header_->count - idx_) * sizeof (*(array)));         \
            }                                                                  \
            memcpy (&(array)[idx_], (items), count_ * sizeof (*(array)));      \
            header_->count += count_;                                          \
        }                                                                      \
    } while (0)

#endif // MINI_ARRAY_H
