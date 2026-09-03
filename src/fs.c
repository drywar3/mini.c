#include "mini.c/fs.h"

#include <unistd.h>
#include <sys/stat.h>

bool mini_fs_exists(const char *filepath) {
    return access(filepath, F_OK) == 0;
}

bool mini_fs_is_directory(const char *filepath) {
    struct stat s;
    if (stat(filepath, &s) != 0)
        return false;
    return S_ISDIR(s.st_mode);
}

bool mini_fs_is_file(const char *filepath);

bool mini_fs_read_into(const char *path, Mini_String *out);
