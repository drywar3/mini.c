#ifndef MINI_FS_H
#define MINI_FS_H

#include "mini.c/allocator.h"
#include "mini.c/string.h"

bool mini_fs_exists(const char *filepath);
bool mini_fs_is_directory(const char *filepath);
bool mini_fs_is_file(const char *filepath);

bool mini_fs_read_into(const char *path, Mini_String *out);

#endif // MINI_FS_H
