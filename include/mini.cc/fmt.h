#pragma once

#include <mini.c/string.h>

namespace mini
{
    Mini_String format(Mini_Allocator allocator, const char *fmt, ...);
} // namespace mini
