#ifndef MINI_RECORD_ALLOCATOR_H
#define MINI_RECORD_ALLOCATOR_H

#include "mini.c/allocator.h"
#include "mini.c/array.h"

typedef struct {
    Mini_Allocator base_allocator;
    MINI_ARRAY(void*) allocations;
} Mini_RecordAllocator;

Mini_RecordAllocator mini_rda_create(Mini_Allocator base);
void mini_rda_destroy(Mini_RecordAllocator *rda);

Mini_Allocator mini_rda_allocator(Mini_RecordAllocator *rda);

#endif // MINI_RECORD_ALLOCATOR_H
