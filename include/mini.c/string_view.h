#ifndef MINI_C_STRING_VIEW_H
#define MINI_C_STRING_VIEW_H

#include "mini.c/mini_def.h"
#include "mini.c/allocator.h"
#include "mini.c/string.h"

#ifndef SVARG
# define SVARG(sv) (int)sv.length, sv.data
#endif

typedef struct {
    const char *data;
    usize length;
} Mini_StringView;

Mini_StringView mini_sv_init(const char *data, usize length);
Mini_StringView mini_sv_from_cstr(const char *string);

Mini_StringView mini_sv_trimr(Mini_StringView sv);
Mini_StringView mini_sv_triml(Mini_StringView sv);
Mini_StringView mini_sv_trim(Mini_StringView sv);

bool mini_sv_contains(Mini_StringView sv, char ch);
bool mini_sv_contains_cstr(Mini_StringView sv, const char *str);

bool mini_sv_begins_with(Mini_StringView sv, const char *prefix);
bool mini_sv_ends_with(Mini_StringView sv, const char *suffix);

bool mini_sv_equals(Mini_StringView sv1, Mini_StringView sv2);
bool mini_sv_equals_cstr(Mini_StringView sv1, const char *str);

Mini_String mini_sv_to_string(Mini_StringView sv, Mini_Allocator allocator);

#endif // MINI_C_STRING_VIEW_H
