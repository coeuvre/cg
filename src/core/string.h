#ifndef CG_CORE_STRING_H
#define CG_CORE_STRING_H

#include "core/utils.h"

// Find `ch` in `str` from right.
//
// Return a pointer to the first occurrence of `ch` in `str`.
// If the `ch` is not found, return NULL
static inline char *find_str_right(char *str, usize size, char ch)
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
static inline usize copy_str(char *dst, usize dst_size, char *src, usize src_size)
{
    usize copied = 0;
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

static inline usize concat_str(char *dst, usize dst_size, char *src1, usize src1_size, char *src2, usize src2_size)
{
    usize size = copy_str(dst, dst_size, src1, src1_size);
    if (size == src1_size) {
        ASSERT(dst_size >= size);
        size += copy_str(dst + size, dst_size - size, src2, src2_size);
    }
    return size;
}

// Push `src` into `dst` at offset `at`.
//
// Return the length of result string.
static inline usize push_str(char *dst, usize dst_size, usize at, char *src, usize src_size)
{
    usize size = at;
    if (at < dst_size) {
        size += copy_str(dst + at, dst_size - at, src, src_size);
    } else {
        size = dst_size;
    }
    return size;
}

#endif
