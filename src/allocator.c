#include "mini.c/allocator.h"

Mini_Allocator mini_create_allocator (void *context, Mini_AllocProcedure alloc,
                                      Mini_ReallocProcedure realloc,
                                      Mini_FreeProcedure free)
{
    int capabilities = 0;
    if (alloc)
        capabilities |= MINI_ALLOCATOR_CAN_ALLOC;
    if (realloc)
        capabilities |= MINI_ALLOCATOR_CAN_REALLOC;
    if (free)
        capabilities |= MINI_ALLOCATOR_CAN_FREE;
    return (Mini_Allocator){alloc, realloc, free, context, capabilities};
}

void *mini_allocator_alloc (Mini_Allocator allocator, usize size,
                            Mini_SourceLocation srcloc)
{
    if ((allocator.capabilities & MINI_ALLOCATOR_CAN_ALLOC) ==
        MINI_ALLOCATOR_CAN_ALLOC)
        return allocator.alloc_proc (allocator.context, size, srcloc);
    return NULL;
}

void *mini_allocator_realloc (Mini_Allocator allocator, void *old_ptr,
                              usize new_size, Mini_SourceLocation srcloc)
{
    if ((allocator.capabilities & MINI_ALLOCATOR_CAN_REALLOC) ==
        MINI_ALLOCATOR_CAN_REALLOC)
        return allocator.realloc_proc (allocator.context, old_ptr, new_size,
                                       srcloc);
    return NULL;
}

void mini_allocator_free (Mini_Allocator allocator, void *ptr,
                          Mini_SourceLocation srcloc)
{
    if ((allocator.capabilities & MINI_ALLOCATOR_CAN_FREE) ==
        MINI_ALLOCATOR_CAN_FREE)
        allocator.free_proc (allocator.context, ptr, srcloc);
}
