#include "mini.c/allocator.h"

Mini_Allocator mini_create_allocator (void *context, Mini_AllocProcedure alloc,
                                      Mini_ReallocProcedure realloc,
                                      Mini_FreeProcedure free)
{
    return (Mini_Allocator){alloc, realloc, free, context};
}

void *mini_allocator_alloc (Mini_Allocator allocator, usize size,
                            Mini_SourceLocation srcloc)
{
    return allocator.alloc_proc (allocator.context, size, srcloc);
}
void *mini_allocator_realloc (Mini_Allocator allocator, void *old_ptr,
                              usize new_size, Mini_SourceLocation srcloc);

void mini_allocator_free (Mini_Allocator allocator, void *ptr,
                          Mini_SourceLocation srcloc)
{
    allocator.free_proc (allocator.context, ptr, srcloc);
}
