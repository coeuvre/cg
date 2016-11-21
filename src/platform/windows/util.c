#include <stdio.h>

#include "platform/windows/util.h"

size_t
get_executable_dir(char *buf, size_t size)
{
    size_t len = GetModuleFileName(NULL, buf, (DWORD)size);
    if (len == size) {
        assert(!"Buffer is too small");
        return size;
    } else {
        // Change the char after last `\\` to `\0`
        char *p = cg_str_rfind(buf, len, '\\');
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
