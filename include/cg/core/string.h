#ifndef CGCORE_STRING_H
#define CGCORE_STRING_H

#include <cg/core/prim.h>

/*
 * Count the size of NULL terminated string `str` in bytes.
 */
CGuint cgGetCStrSize(char *str);

/*
 * Count the number of characters of NULL terminated string `str`.
 */
CGuint cgGetCStrCount(char *str);

/*
 * Test whether two strings `str1` and `str2` are equal.
 */
CGbool cgIsCStrEqual(char *str1, char *str2);

/*
 * Given a string `str` with length `count` (not including the NULL character),
 * find `ch` in it from right.
 *
 * Return the index of first occurrence of `ch` in `str`, or CG_INVALID_INDEX
 * if the `ch` is not found.
 */
CGint cgFindCStrReversed(char *str, char ch);

/*
 * Copy string from `src` into `dst` with NULL terminated.
 *
 * Return the number of characters had copied (not including the terminating
 * NULL character).
 */
size_t cgCopyCStr(char *dst, CGuint dstSize, char *src);

typedef struct CGStr {
    CGi8 *buf;
    CGuint used;
    CGuint size;
} CGStr;

#endif // CGCORE_STRING_H
