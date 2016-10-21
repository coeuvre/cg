CG_VLOG(vlog)
{
    (void)level;

    char buf[512];
    _vsnprintf_s(buf, 512, 511, format, args);
    buf[511] = 0;
    OutputDebugString(buf);
}

CG_LOG(cg_log)
{
    (void)level;
    va_list args;
    va_start(args, format);
    vlog(level, format, args);
    va_end(args);
}

static usize get_executable_dir(char *buf, usize size)
{
    usize len = GetModuleFileName(NULL, buf, (DWORD)size);
    if (len == size) {
        ASSERT(!"Buffer is too small");
        return size;
    } else {
        // Change the char after last `\\` to `\0`
        char *p = find_str_right(buf, len, '\\');
        if (p) {
            ++p;
            *p = 0;
            return p - buf;
        } else {
            ASSERT(!"Bad Executable Path");
            return len;
        }
    }
}

static usize get_executable_name(char *buf, usize size)
{
    usize len = GetModuleFileName(NULL, buf, (DWORD)size);
    if (len == size) {
        ASSERT(!"Buffer is too small");
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
            ASSERT(!"Bad Executable Path");
            return len;
        }
    }
}

static inline FILETIME get_last_write_time(char *filename)
{
    FILETIME time = {0};

    WIN32_FILE_ATTRIBUTE_DATA data;
    if (GetFileAttributesEx(filename, GetFileExInfoStandard, &data)) {
        time = data.ftLastWriteTime;
    }

    return time;
}

static inline i64 get_current_counter()
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return counter.QuadPart;
}

static inline f32 get_seconds_elapsed(i64 start, i64 end)
{
    static i64 freq = 0;

    if (freq == 0) {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        freq = f.QuadPart;
    }

    return (f32)(end - start) / (f32)freq;
}
