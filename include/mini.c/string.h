#ifndef MINI_STRING_H
#define MINI_STRING_H

#include "mini.c/allocator.h"
#include "mini.c/array.h"
#include "mini.c/mini_def.h"
#include <stdbool.h>

typedef MINI_ARRAY (char) Mini_String;

Mini_String mini_string_init (Mini_Allocator allocator);
Mini_String mini_string_build (Mini_Allocator allocator, const char *fmt, ...);
Mini_String mini_string_from_cstr (Mini_Allocator allocator, const char *s);

bool mini_string_equals (Mini_String one, Mini_String two);

const char *mini_string_cstr (Mini_String string);

void mini_string_append (Mini_String *string, char c);
void mini_string_append_string (Mini_String *string, const char *s);
void mini_string_append_fmt (Mini_String *string, const char *fmt, ...);

usize mini_string_count (Mini_String string);

#endif // MINI_STRING_H
