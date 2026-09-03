#include "mini.c/string_view.h"

const char *BOOL(bool t) {
    if (t) return "true";
    return "false";
}

int main() {
    Mini_StringView sv = mini_sv_from_cstr("trea");
    printf("[1] %s\n", BOOL(mini_sv_begins_with(sv, "tr")));
    printf("[2] %s\n", BOOL(mini_sv_ends_with(sv, "rea")));
    printf("[3] %s\n", !BOOL(mini_sv_ends_with(sv, "foobar")));
    printf("[4] %s\n", BOOL(mini_sv_contains(sv, 'e')));
    printf("[5] %s\n", BOOL(mini_sv_contains_cstr(sv, "rea")));

    sv = mini_sv_from_cstr("    foo");
    sv = mini_sv_triml(sv);

    printf("trimmed: '%.*s'\n", SVARG(sv));
}
