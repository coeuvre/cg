#include <stdio.h>

#include <cg/core.h>

#include <Windows.h>

int64_t cg_get_current_counter(void)
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return counter.QuadPart;
}

int64_t cg_counter_to_nanosec(int64_t counter)
{
    static int64_t freq = 0;

    if (freq == 0) {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        freq = f.QuadPart;
    }

    int64_t nanosec = counter * 1000000000 / freq;

    return nanosec;
}

#if 0
#include "platform/windows/utils.h"

size_t
get_executable_dir(char *buf, size_t size)
{
    size_t len = GetModuleFileName(NULL, buf, (DWORD)size);
    if (len == size) {
        assert(!"Buffer is too small");
        return size;
    } else {
        // Change the char after last `\\` to `\0`
        char *p = cg_cstr_rfind(buf, len, '\\');
        if (p) {
            ++p;
            *p = 0;
            return p - buf;
        } else {
            assert(!"Bad Executable Path");
            return len;
        }
    }
}

size_t
get_executable_name(char *buf, size_t size)
{
    size_t len = GetModuleFileName(NULL, buf, (DWORD)size);
    if (len == size) {
        assert(!"Buffer is too small");
        return size;
    } else {
        char *p = cg_str_rfind(buf, len, '\\');
        if (p) {
            char *src = p + 1;
            char *dst = buf;
            while (*src) {
                *dst++ = *src++;
            }
            *dst = 0;
            return dst - buf;
        } else {
            assert(!"Bad Executable Path");
            return len;
        }
    }
}
#endif