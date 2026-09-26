#include <mini.cc/string_view.h>

mini::StringView::StringView() : base_(mini_sv_from_cstr("")) {}

mini::StringView::StringView(const char *s) : base_(mini_sv_from_cstr(s)) {}
mini::StringView::StringView(const char *s, usize length) : base_(mini_sv_init(s, length)) {}
