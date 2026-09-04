#include "mini.c/debug_allocator.h"
#include "mini.c/default_allocator.h"

Mini_DebugAllocator mini_dba_create() {
    return mini_dba_create_with_allocator(mini_default_allocator());
}

Mini_DebugAllocator mini_dba_create_with_allocator(Mini_Allocator allocator) {
    Mini_DebugAllocator dba = {0};
    dba.allocator = allocator;
    dba.records   = MINI_ARRAY_INIT(allocator, Mini_DebugAllocRecord);
    return dba;
}

void mini_dba_destroy(Mini_DebugAllocator *dba, bool report_leaks) {
    usize leak_count = 0;
    for (usize n = 0; n < mini_array_count(dba->records); ++n) {
        Mini_DebugAllocRecord record = dba->records[n];
        if (record.memory != NULL) {
            if (report_leaks)
                fprintf(stderr, "[mini.debug]: %s:%d: leak (%p) detected\n",
                        record.src.filename, record.src.line, record.memory);
            leak_count += 1;
        }
    }
    if (report_leaks)
        fprintf(stderr, "[mini.debug]: %zu leak[s] detected\n", leak_count);
    mini_array_destroy(dba->records);
}

static void *__alloc(void *_dba, usize size, Mini_SourceLocation srcloc) {
    Mini_DebugAllocator *dba = (Mini_DebugAllocator*)_dba;
    void *pointer = mini_allocator_alloc(dba->allocator, size, srcloc);
    Mini_DebugAllocRecord record = {0};
    record.size   = size;
    record.src    = srcloc;
    record.memory = pointer;

    for (usize n = 0; n < mini_array_count(dba->records); ++n) {
        // This record isn't being used so reuse it.
        if (dba->records[n].memory == NULL) {
            dba->records[n] = record;
            return pointer;
        }
    }

    mini_array_append(dba->records, record);
    return pointer;
}

static void __free (void *_dba, void *ptr, Mini_SourceLocation srcloc) {
    Mini_DebugAllocator *dba = (Mini_DebugAllocator*)_dba;
    for (usize n = 0; n < mini_array_count(dba->records); ++n) {
        Mini_DebugAllocRecord *record = &dba->records[n];
        if (record->memory == ptr) {
            record->memory = NULL;
            mini_allocator_free(dba->allocator, ptr, srcloc);
            return;
        }
    }
    MINI_PANIC("[debug allocator]: attempt to free foreign pointer");
}

static void *__realloc (void *_dba, void *ptr, usize size, Mini_SourceLocation srcloc) {
    Mini_DebugAllocator *dba = (Mini_DebugAllocator*)_dba;
    for (usize n = 0; n < mini_array_count(dba->records); ++n) {
        if (dba->records[n].memory == ptr) {
            dba->records[n].src    = srcloc;
            dba->records[n].memory = mini_allocator_realloc(dba->allocator, ptr, size, srcloc);
            return dba->records[n].memory;
        }
    }
    MINI_PANIC("[debug allocator]: attempt to reallocate foriegn pointer");
}

Mini_Allocator mini_dba_allocator(Mini_DebugAllocator *dba) {
    return mini_create_allocator(dba, __alloc, __realloc, __free);
}
