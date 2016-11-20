#ifndef CG_CORE_STRING_H
#define CG_CORE_STRING_H

#include <cg/core/prim.h>

/*
 * Given a string `str` with length `size` (not including the NULL character),
 * find `ch` in it from right.
 *
 * Return a pointer to the first occurrence of `ch` in `str`, or NULL if the
 * `ch` is not found.
 */
char *cg_str_rfind(char *str, size_t size, char ch);

/*
 * Copy string from `src` into `dst` with NULL terminated.
 *
 * Return the number of characters had copied (not including the terminating
 * NULL character).
 */
size_t cg_str_copy(char *dst, size_t dst_size, char *src, size_t src_size);

size_t cg_str_concat(char *dst, size_t dst_size, char *src1, size_t src1_size,
                     char *src2, size_t src2_size);

/*
 * Push `src` into `dst` at offset `at`.
 *
 * Return the length of result string.
 */
size_t cg_str_push(char *dst, size_t dst_size, size_t at,
                   char *src, size_t src_size);

#endif /* CG_CORE_STRING_H */
