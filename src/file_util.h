#ifndef TERM_FILE_UTIL_H
#define TERM_FILE_UTIL_H

#include "file_ops.h"

struct EntireFile {
    void *buf;
    size_t size;
};


int ReadEntireFile(const char *path,struct EntireFile *file_buf);

#endif