#include "mini.c/fs.h"

#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h> // realpath, free
#include <stdio.h>

bool mini_fs_exists(const char *filepath) {
    return access(filepath, F_OK) == 0;
}

bool mini_fs_is_directory(const char *filepath) {
    struct stat s;
    if (stat(filepath, &s) != 0)
        return false;
    return S_ISDIR(s.st_mode);
}

bool mini_fs_is_file(const char *filepath) {
    struct stat s;
    if (stat(filepath, &s) != 0)
        return false;
    return S_ISREG(s.st_mode);
}

bool mini_fs_read_into(const char *path, Mini_String *out) {
    if (!mini_fs_is_file(path))
        return false;

    FILE *file = fopen(path, "rb");
    if (!file)
        return false;

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            mini_string_append(out, buffer[i]);
        }
    }

    fclose(file);
    return true;
}

bool mini_fs_canonicalize(const char *path, Mini_String *out) {
    if (!path || !out)
        return false;

    char *resolved = realpath(path, NULL);
    if (!resolved)
        return false;

    for (const char *p = resolved; *p != '\0'; ++p) {
        mini_string_append(out, *p);
    }

    free(resolved);
    return true;
}
