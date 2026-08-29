#ifndef MINI_ALLOCATOR_H
#define MINI_ALLOCATOR_H

#include "mini.c/mini_def.h"

#define MINI_ALLOC(allocator, T)                                               \
    mini_allocator_alloc (allocator, sizeof (T), $M)
#define MINI_ALLOC_MANY(allocator, T, count)                                   \
    mini_allocator_alloc (allocator, sizeof (T) * count, $M)

#define MINI_REALLOC(allocator, pointer, new_size)                             \
    mini_allocator_realloc (allocator, pointer, new_size, $M)
#define MINI_FREE(allocator, pointer)                                          \
    mini_allocator_free (allocator, pointer, $M)

typedef void *(*Mini_AllocProcedure) (void *context, usize size,
                                      Mini_SourceLocation);
typedef void *(*Mini_ReallocProcedure) (void *context, void *old_ptr,
                                        usize new_size, Mini_SourceLocation);
typedef void (*Mini_FreeProcedure) (void *context, void *ptr,
                                    Mini_SourceLocation);

typedef struct
{
    Mini_AllocProcedure alloc_proc;
    Mini_ReallocProcedure realloc_proc;
    Mini_FreeProcedure free_proc;
    void *context;
} Mini_Allocator;

Mini_Allocator mini_create_allocator (void *context, Mini_AllocProcedure alloc,
                                      Mini_ReallocProcedure realloc,
                                      Mini_FreeProcedure free);

void *mini_allocator_alloc (Mini_Allocator allocator, usize size,
                            Mini_SourceLocation srcloc);
void *mini_allocator_realloc (Mini_Allocator allocator, void *old_ptr,
                              usize new_size, Mini_SourceLocation srcloc);
void mini_allocator_free (Mini_Allocator allocator, void *ptr,
                          Mini_SourceLocation srcloc);

#endif // MINI_ALLOCATOR_H
