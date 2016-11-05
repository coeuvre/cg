#ifndef CG_CORE_STRING_H
#define CG_CORE_STRING_H

#include "core/utils.h"

// Find `ch` in `str` from right.
//
// Return a pointer to the first occurrence of `ch` in `str`.
// If the `ch` is not found, return NULL
static inline char *cg_str_rfind(char *str, size_t size, char ch)
{
    char *p = str + size - 1;
    while (p >= str) {
        if (*p == ch) {
            return p;
        }
        --p;
    }
    return NULL;
}

// Copy string from `src` into `dst` with NULL terminated.
//
// Return the number of characters copied (not including the terminating NULL character).
static inline size_t cg_str_copy(char *dst, size_t dst_size, char *src, size_t src_size)
{
    size_t copied = 0;
    while (dst_size > 0 && src_size > 0) {
        *dst++ = *src++;
        --dst_size;
        --src_size;
        ++copied;
    }

    if (dst_size > 0) {
        *dst = 0;
    } else {
        *--dst = 0;
        --copied;
    }
    return copied;
}

static inline size_t cg_str_concat(char *dst, size_t dst_size, char *src1, size_t src1_size, char *src2, size_t src2_size)
{
    size_t size = cg_str_copy(dst, dst_size, src1, src1_size);
    if (size == src1_size) {
        assert(dst_size >= size);
        size += cg_str_copy(dst + size, dst_size - size, src2, src2_size);
    }
    return size;
}

// Push `src` into `dst` at offset `at`.
//
// Return the length of result string.
static inline size_t cg_str_push(char *dst, size_t dst_size, size_t at, char *src, size_t src_size)
{
    size_t size = at;
    if (at < dst_size) {
        size += cg_str_copy(dst + at, dst_size - at, src, src_size);
    } else {
        size = dst_size;
    }
    return size;
}

#endif
