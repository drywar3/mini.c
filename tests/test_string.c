#include "mini.c/array.h"
#include "mini.c/default_allocator.h"
#include "mini.c/string.h"

int main ()
{
    Mini_String string =
        mini_string_build (mini_default_allocator (), "Hello %s", "World");
    mini_string_append_fmt (&string, " This is after append %d", 10);
    mini_array_destroy (string);
}
