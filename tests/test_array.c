#include "mini.c/array.h"
#include "mini.c/default_allocator.h"
#include <stdio.h>

void int_dtor (void *__v)
{
    int value = *((int *)__v);
    printf ("destroying `%d`\n", value);
}

int main ()
{
    MINI_ARRAY (int) numbers = MINI_ARRAY_INIT (mini_default_allocator (), int);
    mini_array_set_dtor (numbers, int_dtor);

    mini_array_append (numbers, 10);
    mini_array_append (numbers, 20);
    mini_array_append (numbers, 30);
    mini_array_append (numbers, 40);

    mini_array_insert (numbers, 1, 60);

    printf ("[0] = %d\n", numbers[0]);
    printf ("[1] = %d\n", numbers[1]);
    printf ("[2] = %d\n", numbers[2]);
    printf ("[3] = %d\n", numbers[3]);

    mini_array_destroy (numbers);
}
