#include "mini.c/string.h"
#include "mini.c/allocator.h"
#include "mini.c/array.h"

#include <stdarg.h>
#include <stdio.h>

Mini_String mini_string_init (Mini_Allocator allocator)
{
    Mini_String string = MINI_ARRAY_INIT (allocator, char);
    mini_array_append (string, '\0');
    return string;
}

Mini_String mini_string_build (Mini_Allocator allocator, const char *fmt, ...)
{
    Mini_String string = mini_string_init (allocator);
    va_list args;
    va_start (args, fmt);

    usize n      = vsnprintf (NULL, 0, fmt, args);
    char *buffer = MINI_ALLOC_MANY (allocator, char, n + 1);
    va_start (args, fmt);
    vsnprintf (buffer, n + 1, fmt, args);

    mini_string_append_string (&string, buffer);

    MINI_FREE (allocator, buffer);
    return string;
}

Mini_String mini_string_from_cstr (Mini_Allocator allocator, const char *s)
{
    return mini_string_build (allocator, "%s", s);
}

bool mini_string_equals (Mini_String one, Mini_String two);

const char *mini_string_cstr (Mini_String string);

void mini_string_append (Mini_String *string, char c)
{
    usize count = mini_array_count (*string);
    mini_array_insert (*string, count - 1, c);
}

void mini_string_append_string (Mini_String *string, const char *s)
{
    usize count = mini_array_count (*string);
    mini_array_insert_range (*string, count - 1, s, strlen (s));
}

void mini_string_append_fmt (Mini_String *string, const char *fmt, ...)
{
    Mini_ArrayHeader_ *header = MINI_ARRAY_HDR (*string);
    Mini_Allocator allocator  = header->allocator;
    va_list args;
    va_start (args, fmt);
    usize n      = vsnprintf (NULL, 0, fmt, args);
    char *buffer = MINI_ALLOC_MANY (allocator, char, n + 1);
    va_start (args, fmt);
    vsnprintf (buffer, n + 1, fmt, args);
    mini_string_append_string (string, buffer);
    MINI_FREE (allocator, buffer);
}

usize mini_string_count (Mini_String string)
{
    return mini_array_count (string) - 1;
}
