#include "mini.c/allocator.h"
#include "mini.c/record_allocator.h"
#include "mini.c/mini_def.h"

Mini_RecordAllocator mini_rda_create(Mini_Allocator base) {
    Mini_RecordAllocator rda = {0};
    rda.base_allocator = base;
    rda.allocations = MINI_ARRAY_INIT(base, void*);
    return rda;
}

void mini_rda_destroy(Mini_RecordAllocator *rda) {
    if (!rda) return;
    for (size_t n = 0; n < mini_array_count(rda->allocations); ++n) {
        void *pointer = rda->allocations[n];
        if (pointer) {
            MINI_FREE(rda->base_allocator, pointer);
        }
    }
    mini_array_destroy(rda->allocations);
}

static void *__alloc(void *_rda, usize size, Mini_SourceLocation srcloc) {
    Mini_RecordAllocator *rda = (Mini_RecordAllocator*)_rda;
    void *pointer = mini_allocator_alloc(rda->base_allocator, size, srcloc);
    mini_array_append(rda->allocations, pointer);
    return pointer;
}

static void __free (void *_rda, void *ptr, Mini_SourceLocation srcloc) {
    // NO OP: we free everything later on
}

static void *__realloc (void *_rda, void *ptr, usize size, Mini_SourceLocation srcloc) {
    Mini_RecordAllocator *rda = (Mini_RecordAllocator*)_rda;
    for (usize n = 0; n < mini_array_count(rda->allocations); ++n) {
        if (rda->allocations[n] == ptr) {
            rda->allocations[n] = mini_allocator_realloc(rda->base_allocator, ptr, size, srcloc);
            return rda->allocations[n];
        }
    }
    MINI_PANIC("attempt to reallocate foriegn pointer");
}

Mini_Allocator mini_rda_allocator(Mini_RecordAllocator *rda) {
    return mini_create_allocator((void*)rda, __alloc, __realloc, __free);
}
