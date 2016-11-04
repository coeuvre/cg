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

static inline i64
get_current_counter()
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return counter.QuadPart;
}

static inline f32
get_seconds_elapsed(i64 start, i64 end)
{
    static i64 freq = 0;

    if (freq == 0) {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        freq = f.QuadPart;
    }

    return (f32)(end - start) / (f32)freq;
}

VLOG(vlog);
CG_ALLOC(cg_alloc);
CG_FREE(cg_free);

usize get_executable_dir(char *buf, usize size);
usize get_executable_name(char *buf, usize size);

#endif // CG_PLATFORM_WINDOW_UTILS_H
