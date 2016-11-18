#include <stdio.h>

#include "utils.h"

CG_VLOG(cg_vlog)
{
    (void)level;

#define MAX_CHAR_COUNT 512
    char buf[MAX_CHAR_COUNT];
    int written = vsnprintf_s(buf, MAX_CHAR_COUNT, MAX_CHAR_COUNT - 2, format, args);
    if (written < 0) {
        written = MAX_CHAR_COUNT - 2;
    }
    buf[written++] = '\n';
    buf[written] = 0;

#if defined(CG_COMPILER_MSVC)
    OutputDebugString(buf);
#else
    vprintf(format, args);
#endif
}

CG_LOG(cg_log)
{
    (void)level;
    va_list args;
    va_start(args, format);
    cg_vlog(level, format, args);
    va_end(args);
}

CG_ALLOC(cg_alloc)
{
    size_t *p = VirtualAlloc(0, size + sizeof(size_t), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    *p = size;
    return p + 1;
}

CG_FREE(cg_free)
{
    size_t *origin = (size_t *)p - 1;
    assert(*origin == size);
    VirtualFree(origin, 0, MEM_RELEASE);
}

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
