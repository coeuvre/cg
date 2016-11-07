#ifndef CG_CORE_H
#define CG_CORE_H

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef _WIN32
#define CG_PLATFORM_WINDOWS
#else
#error Unsuporrted platform
#endif

#ifdef CG_PLATFORM_WINDOWS
#define CG_EXPORT __declspec(dllexport)
#else
#define CG_EXPORT
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Utils
//

#define cg_assert(expr) assert(expr)

#define cg_array_count(a) (sizeof(a) / sizeof(a[0]))

#define cg_size_kb(x) ((x) * 1024LL)
#define cg_size_mb(x) (cg_size_kb(x) * 1024LL)
#define cg_size_gb(x) (cg_size_mb(x) * 1024LL)
#define cg_size_tb(x) (cg_size_gb(x) * 1024LL)

////////////////////////////////////////////////////////////////////////////////
//
// String
//

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
    return 0;
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

////////////////////////////////////////////////////////////////////////////////
//
// Log
//

typedef enum cgLogLevel {
    cgLogLevel_Error,
    cgLogLevel_Warn,
    cgLogLevel_Info,
    cgLogLevel_Debug,
    cgLogLevel_Trace,
} cgLogLevel;

#define CG_VLOG(name) void name(cgLogLevel level, char *format, va_list args)
typedef CG_VLOG(cgVLog);

#define CG_LOG(name) void name(cgLogLevel level, char *format, ...)
typedef CG_LOG(cgLog);

extern CG_LOG(cg_log);

#define cg_error(format, ...) cg_log(cgLogLevel_Error, format, __VA_ARGS__)
#define cg_warn(format, ...) cg_log(cgLogLevel_Warn, format, __VA_ARGS__)
#define cg_info(format, ...) cg_log(cgLogLevel_Info, format, __VA_ARGS__)
#define cg_debug(format, ...) cg_log(cgLogLevel_Debug, format, __VA_ARGS__)
#define cg_trace(format, ...) cg_log(cgLogLevel_Trace, format, __VA_ARGS__)

#endif // CG_CORE_H
