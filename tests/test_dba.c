#include "mini.c/debug_allocator.h"
#include <stdlib.h>

int main() {
    Mini_DebugAllocator dba = mini_dba_create();
    Mini_Allocator allocator = mini_dba_allocator(&dba);

    char *alphabets = MINI_ALLOC_MANY(allocator, char, 26);
    MINI_FREE(allocator, alphabets);

    MINI_ASSERT(!mini_dba_has_leaks(&dba), "memory leak detected");

    char *foreign_memory = malloc(100);
    MINI_ASSERT(mini_dba_is_foreign(&dba, foreign_memory), "memory should be foreign");

    // double-free test
    MINI_ASSERT(mini_dba_is_foreign(&dba, alphabets), "memory should be foreign after free");

    mini_dba_destroy(&dba, true);
}
