#ifndef CG_PLATFORM_WINDOW_UTILS_H
#define CG_PLATFORM_WINDOW_UTILS_H

#include "core/types.h"
#include "core/utils.h"
#include "core/string.h"
#include "platform/platform.h"

#include <Windows.h>

static inline FILETIME
get_last_write_time(char *filename)
{
    FILETIME time = {0};

    WIN32_FILE_ATTRIBUTE_DATA data;
    if (GetFileAttributesEx(filename, GetFileExInfoStandard, &data)) {
        time = data.ftLastWriteTime;
    }

    return time;
}

static inline int64_t
get_current_counter()
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return counter.QuadPart;
}

static inline float
get_seconds_elapsed(int64_t start, int64_t end)
{
    static int64_t freq = 0;

    if (freq == 0) {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        freq = f.QuadPart;
    }

    return (float)(end - start) / (float)freq;
}

CG_VLOG(cg_vlog);
CG_ALLOC(cg_alloc);
CG_FREE(cg_free);

size_t get_executable_dir(char *buf, size_t size);
size_t get_executable_name(char *buf, size_t size);

#endif // CG_PLATFORM_WINDOW_UTILS_H
