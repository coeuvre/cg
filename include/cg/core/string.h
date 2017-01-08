#ifndef CGCORE_STRING_H
#define CGCORE_STRING_H

#include <cg/core/prim.h>

/*
 * Count the size of NULL terminated string `str` in bytes.
 */
CGusize cgGetCStrSize(CGi8 *str);

/*
 * Count the number of characters of NULL terminated string `str`.
 */
CGusize cgGetCStrCount(CGi8 *str);

/*
 * Test whether two strings `str1` and `str2` are equal.
 */
CGbool cgIsCStrEqual(CGi8 *str1, CGi8 *str2);

/*
 * Given a string `str` with length `count` (not including the NULL character),
 * find `ch` in it from right.
 *
 * Return the index of first occurrence of `ch` in `str`, or CG_INVALID_INDEX
 * if the `ch` is not found.
 */
CGindex cgFindCStrReversed(CGi8 *str, CGi8 ch);

/*
 * Copy string from `src` into `dst` with NULL terminated.
 *
 * Return the number of characters had copied (not including the terminating
 * NULL character).
 */
size_t cgCopyCStr(char *dst, size_t dstSize, char *src);

typedef struct CGStr {
    CGi8 *buf;
    CGusize used;
    CGusize size;
} CGStr;

#endif /* CGCORE_STRING_H */
