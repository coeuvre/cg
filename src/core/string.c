#include <cg/core.h>

/*
 * TODO: utf-8
 */

size_t cg_cstr_size(char *str)
{
    size_t ret = 0;

    while (*str++) {
        ++ret;
    }

    return ret;
}

size_t cg_cstr_count(char *str)
{
    size_t ret = 0;

    while (*str++) {
        ++ret;
    }

    return ret;
}

bool cg_cstr_is_equal(char *str1, char *str2)
{
    bool ret = true;

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

CGsize cg_cstr_rfind(char *str, char ch)
{
    CGsize ret = CGINVALID_INDEX;

    char *p = str;

    char t;
    while ((t = *p++)) {
        if (t == ch) {
            ret = p - str - 1;
        }
    }

    return ret;
}

size_t cg_cstr_copy(char *dst, size_t dst_size, char *src)
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
