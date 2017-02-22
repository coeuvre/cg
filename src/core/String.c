#include <cg/Core.h>

/*
 * TODO: utf-8
 */

CGuint cgGetCStrSize(char *str)
{
    CGuint ret = 0;

    while (*str++) {
        ++ret;
    }

    return ret;
}

CGuint cgGetCStrCount(char *str)
{
    CGuint ret = 0;

    while (*str++) {
        ++ret;
    }

    return ret;
}

CGbool cgIsCStrEqual(char *str1, char *str2)
{
    CGbool ret = true;

    char *p1 = str1, *p2 = str2;
    char ch1, ch2;
    for (;;) {
        ch1 = *p1++, ch2 = *p2++;

        if (ch1 != ch2) {
            ret = false;
            break;
        } else if (ch1 == 0) {
            break;
        }
    }

    return ret;
}

CGint cgFindCStrReversed(char *str, char ch)
{
    CGint ret = CG_INVALID_INDEX;

    char *p = str;

    char t;
    while ((t = *p++)) {
        if (t == ch) {
            ret = p - str - 1;
        }
    }

    return ret;
}

CGuint cgCopyCStr(char *dst, CGuint dst_size, char *src)
{
    char *pd = dst;
    char *end = dst + dst_size;

    char *ps = src;
    char ch;
    while ((pd < end) &&  (ch = *ps++)) {
        *pd++ = ch;
    }

    if (pd < end) {
        *pd = 0;
    } else {
        *--pd = 0;
    }

    return pd - dst;
}
