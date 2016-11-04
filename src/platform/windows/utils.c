#include <stdio.h>

#include "utils.h"

VLOG(vlog)
{
    (void)level;

    char buf[512];
    _vsnprintf_s(buf, 512, 511, format, args);
    buf[511] = 0;
    OutputDebugString(buf);
}

LOG(log)
{
    (void)level;
    va_list args;
    va_start(args, format);
    vlog(level, format, args);
    va_end(args);
}

CG_ALLOC(cg_alloc)
{
    usize *p = VirtualAlloc(0, size + sizeof(usize), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    *p = size;
    return p + 1;
}

CG_FREE(cg_free)
{
    usize *origin = (usize *)p - 1;
    assert(*origin == size);
    VirtualFree(origin, 0, MEM_RELEASE);
}

usize
get_executable_dir(char *buf, usize size)
{
    usize len = GetModuleFileName(NULL, buf, (DWORD)size);
    if (len == size) {
        assert(!"Buffer is too small");
        return size;
    } else {
        // Change the char after last `\\` to `\0`
        char *p = find_str_right(buf, len, '\\');
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

usize
get_executable_name(char *buf, usize size)
{
    usize len = GetModuleFileName(NULL, buf, (DWORD)size);
    if (len == size) {
        assert(!"Buffer is too small");
        return size;
    } else {
        char *p = find_str_right(buf, len, '\\');
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
