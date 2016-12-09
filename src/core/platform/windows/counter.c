#include <stdio.h>

#include <cg/core.h>

#include <Windows.h>

uint64_t cg_current_counter(void)
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return counter.QuadPart;
}

uint64_t cg_counter2ns(uint64_t counter)
{
    static uint64_t freq = 0;

    if (freq == 0) {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        freq = f.QuadPart;
    }

    uint64_t nanosec = counter * 1000000000 / freq;

    return nanosec;
}
