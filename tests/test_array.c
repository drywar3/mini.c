#include "mini.c/array.h"
#include "mini.c/default_allocator.h"

int main ()
{
    MINI_ARRAY (int) numbers = MINI_ARRAY_INIT (mini_default_allocator (), int);

    MINI_ARRAY_APPEND (numbers, 10);
    MINI_ARRAY_APPEND (numbers, 20);
    MINI_ARRAY_APPEND (numbers, 30);
    MINI_ARRAY_APPEND (numbers, 40);

    printf ("[0] = %d\n", numbers[0]);
    printf ("[1] = %d\n", numbers[1]);
    printf ("[2] = %d\n", numbers[2]);
    printf ("[3] = %d\n", numbers[3]);
}
