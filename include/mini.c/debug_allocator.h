#ifndef MINI_C_DEBUG_ALLOCATOR_H
#define MINI_C_DEBUG_ALLOCATOR_H

#include "mini.c/allocator.h"
#include "mini.c/mini_def.h"
#include "mini.c/allocator.h"
#include "mini.c/array.h"

typedef struct {
    Mini_SourceLocation src;
    void *memory;
    usize size;
} Mini_DebugAllocRecord;

typedef struct {
    MINI_ARRAY(Mini_DebugAllocRecord) records;
    Mini_Allocator allocator;
} Mini_DebugAllocator;

Mini_DebugAllocator mini_dba_create();
Mini_DebugAllocator mini_dba_create_with_allocator(Mini_Allocator allocator);

void mini_dba_destroy(Mini_DebugAllocator *dba, bool report_leaks);
Mini_Allocator mini_dba_allocator(Mini_DebugAllocator *dba);

#endif // MINI_C_DEBUG_ALLOCATOR_H
