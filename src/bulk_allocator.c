#include "mini.c/allocator.h"
#include "mini.c/bulk_allocator.h"
#include "mini.c/mini_def.h"

Mini_BulkAllocator mini_blk_create(Mini_Allocator base) {
    Mini_BulkAllocator blk = {0};
    blk.base_allocator = base;
    blk.allocations = MINI_ARRAY_INIT(base, void*);
    return blk;
}

void mini_blk_destroy(Mini_BulkAllocator *blk) {
    if (!blk) return;
    for (size_t n = 0; n < mini_array_count(blk->allocations); ++n) {
        void *pointer = blk->allocations[n];
        if (pointer) {
            MINI_FREE(blk->base_allocator, pointer);
        }
    }
    mini_array_destroy(blk->allocations);
}

static void *__alloc(void *_blk, usize size, Mini_SourceLocation srcloc) {
    Mini_BulkAllocator *blk = (Mini_BulkAllocator*)_blk;
    void *pointer = mini_allocator_alloc(blk->base_allocator, size, srcloc);
    mini_array_append(blk->allocations, pointer);
    return pointer;
}

static void __free (void *_blk, void *ptr, Mini_SourceLocation srcloc) {
    // NO OP: we free everything later on
}

static void *__realloc (void *_blk, void *ptr, usize size, Mini_SourceLocation srcloc) {
    Mini_BulkAllocator *blk = (Mini_BulkAllocator*)_blk;
    for (usize n = 0; n < mini_array_count(blk->allocations); ++n) {
        if (blk->allocations[n] == ptr) {
            blk->allocations[n] = mini_allocator_realloc(blk->base_allocator, ptr, size, srcloc);
            return blk->allocations[n];
        }
    }
    MINI_PANIC("attempt to reallocate foriegn pointer");
}

Mini_Allocator mini_blk_allocator(Mini_BulkAllocator *blk) {
    return mini_create_allocator((void*)blk, __alloc, __realloc, __free);
}
