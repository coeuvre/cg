#include <stdio.h>

#include <cg/Core.h>

#include <Windows.h>

CGu64 cgGetTicks(void)
{
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);
    return ticks.QuadPart;
}

CGu64 cgTicksToNanoseconds(CGu64 ticks)
{
    static CGu64 freq = 0;

    if (freq == 0) {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        freq = f.QuadPart;
    }

    CGu64 nanosec = ticks * 1000000000 / freq;

    return nanosec;
}
