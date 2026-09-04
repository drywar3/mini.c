#include "mini.c/debug_allocator.h"
#include <stdlib.h>

int main() {
    Mini_DebugAllocator dba = mini_dba_create();
    Mini_Allocator allocator = mini_dba_allocator(&dba);

    char *alphabets = MINI_ALLOC_MANY(allocator, char, 26);
    MINI_FREE(allocator, alphabets);

    //char *foreign_memory = malloc(100);
    //MINI_FREE(allocator, foreign_memory);

    // double-free test
    MINI_FREE(allocator, alphabets);

    mini_dba_destroy(&dba, true);
}
