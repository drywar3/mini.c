#ifndef MINI_BULK_ALLOCATOR_H
#define MINI_BULK_ALLOCATOR_H

#include "mini.c/allocator.h"
#include "mini.c/array.h"

// BulkAllocator:
//     An allocator backend that allows multiple allocations without matching calls to free.
//
//     It records all allocators made with an existing allocator and bulk-frees everything
//     at the end of its lifetime [mini_rda_destroy]
typedef struct {
    Mini_Allocator base_allocator;
    MINI_ARRAY(void*) allocations;
} Mini_BulkAllocator;

Mini_BulkAllocator mini_bka_create(Mini_Allocator base);
void mini_bka_destroy(Mini_BulkAllocator *rda);

Mini_Allocator mini_bka_allocator(Mini_BulkAllocator *rda);

#endif // MINI_RECORD_ALLOCATOR_H
