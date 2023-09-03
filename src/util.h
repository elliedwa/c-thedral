#ifndef CATHEDRAL_UTIL_H_
#define CATHEDRAL_UTIL_H_
#include <limits.h>
#include <stddef.h>
#define VAR_TO_STR_BIN(x)                                                      \
        obj_to_bin((char[sizeof(x) *CHAR_BIT + 1]){""}, &(x), sizeof(x))

char *obj_to_bin(char *dest, const void *object, size_t osize);
#endif
