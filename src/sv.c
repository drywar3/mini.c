#include "mini.c/string_view.h"
#include <string.h>

Mini_StringView mini_sv_init(const char *data, usize length) {
    Mini_StringView sv = {0};
    sv.data = data;
    sv.length = length;
    return sv;
}

Mini_StringView mini_sv_from_cstr(const char *string) {
    return mini_sv_init(string, strlen(string));
}

Mini_StringView mini_sv_triml(Mini_StringView sv) {
    usize shift = 0;
    for (usize n = 0; n < sv.length; ++n) {
        // TODO: check for all whitespace characters
        if (sv.data[n] != ' ')
            break;
        shift++;
    }
    return mini_sv_init(&sv.data[shift], sv.length - shift);
}

Mini_StringView mini_sv_trimr(Mini_StringView sv) {
    usize length = sv.length;
    for (usize n = sv.length - 1; n >= 0; --n) {
        if (sv.data[n] != ' ')
            break;
        length--;
    }
    return mini_sv_init(sv.data, length);
}

Mini_StringView mini_sv_trim(Mini_StringView sv) {
    return mini_sv_trimr(mini_sv_triml(sv));
}

bool mini_sv_contains(Mini_StringView sv, char ch) {
    for (usize n = 0; n < sv.length; ++n) {
        if (sv.data[n] == ch)
            return true;
    }
    return false;
}

bool mini_sv_contains_cstr(Mini_StringView sv, const char *str) {
    usize str_length = strlen(str);
    for (usize n = 0; n < sv.length; ++n) {
        // check if the remaining portion of the string_view
        // is smaller than the length of [str].
        usize remaining = sv.length - n;
        // if it is, then it cannot match.
        if (str_length > remaining)
            return false;
        if (strncmp(&sv.data[n], str, str_length) == 0)
            return true;
    }
    return false;
}

bool mini_sv_begins_with(Mini_StringView sv, const char *prefix) {
    usize str_length = strlen(prefix);
    // if the [prefix] is longer than length of [sv], then [sv] cannot begin with [prefix]
    if (str_length > sv.length)
        return false;
    return strncmp(sv.data, prefix, str_length) == 0;
}

bool mini_sv_ends_with(Mini_StringView sv, const char *suffix) {
    usize str_length = strlen(suffix);
    // if the [suffix] is longer than length of [sv], then [sv] cannot end with [suffix]
    if (str_length > sv.length)
        return false;
    return strncmp(&sv.data[sv.length - str_length], suffix, str_length) == 0;
}

bool mini_sv_equals(Mini_StringView sv1, Mini_StringView sv2) {
    // if their lengths differ, then they cannot be equal
    if (sv1.length != sv2.length)
        return false;
    return strncmp(sv1.data, sv2.data, sv1.length) == 0;
}

bool mini_sv_equals_cstr(Mini_StringView sv1, const char *str) {
    return mini_sv_equals(sv1, mini_sv_from_cstr(str));
}

Mini_String mini_sv_to_string(Mini_StringView sv, Mini_Allocator allocator) {
    return mini_string_build(allocator, "%.*s", SVARG(sv));
}
