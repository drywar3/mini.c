#include "mini.c/allocator.h"
#include "mini.c/mini_def.h"
#include <stdlib.h>

static void *__alloc (void *_, usize size, Mini_SourceLocation __)
{
    return malloc (size);
}

static void *__realloc (void *_, void *ptr, usize size, Mini_SourceLocation __)
{
    return realloc (ptr, size);
}

static void __free (void *_, void *ptr, Mini_SourceLocation __)
{
    free (ptr);
}

Mini_Allocator mini_default_allocator ()
{
    return mini_create_allocator (NULL, &__alloc, &__realloc, &__free);
}
