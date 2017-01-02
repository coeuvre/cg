#ifndef CG_CORE_STRING_H
#define CG_CORE_STRING_H

#include <cg/core/prim.h>

/*
 * Count the size of NULL terminated string `str`.
 */
size_t cg_cstr_size(char *str);

/*
 * Count the number of characters of NULL terminated string `str`.
 */
size_t cg_cstr_count(char *str);

/*
 * Test whether two strings `str1` and `str2` are equal.
 */
bool cg_cstr_is_equal(char *str1, char *str2);

/*
 * Given a string `str` with length `count` (not including the NULL character),
 * find `ch` in it from right.
 *
 * Return the index of first occurrence of `ch` in `str`, or CGINVALID_INDEX
 * if the `ch` is not found.
 */
CGuint cg_cstr_rfind(char *str, char ch);

/*
 * Copy string from `src` into `dst` with NULL terminated.
 *
 * Return the number of characters had copied (not including the terminating
 * NULL character).
 */
size_t cg_cstr_copy(char *dst, size_t dst_size, char *src);

struct cg_str {
    char *buf;      /* a pointer to the underlying buffer */
    size_t size;    /* the size of the `buf` */
};

void cg_str_init(struct cg_str *str, char *buf, size_t size);
size_t cg_str_set(struct cg_str *str, char *cstr);
size_t cg_str_copy(struct cg_str *dst, struct cg_str *src);

struct cg_dstr {
    char *buf;
    size_t used;
    size_t size;
};

struct cg_dstr *cg_dstr_create(size_t size);
void cg_dstr_delete(struct cg_dstr *dstr);

#endif /* CG_CORE_STRING_H */
