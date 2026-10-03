#pragma once

#include <mini.c/string_view.h>

namespace mini
{
    struct StringView {
    public:
        StringView();
        StringView(const char *s);
        StringView(const char *s, usize length);
        StringView(Mini_StringView s) : base_(s) {}

        bool operator==(const StringView &other) const {
            return mini_sv_equals(base_, other.base_);
        }

        Mini_String to_string() const {
            return mini_sv_to_string(base_, mini_default_allocator());
        }

        Mini_StringView &base() { return base_; }
        const Mini_StringView &base() const { return base_; }
    private:
        Mini_StringView base_;
    };
} // namespace mini
