#include <cg/core/utils.h>

#include <mach/mach_time.h>

uint64_t cgGetTicks(void)
{
    return mach_absolute_time();
}

uint64_t cgTicksToNanoseconds(uint64_t counter)
{
    /*
     * This static variable means this function is NOT thread safe.
     *
     * TODO: Make this thread safe.
     */
    static mach_timebase_info_data_t base;

    if (base.denom == 0) {
        mach_timebase_info(&base);
    }

    return counter * base.numer / base.denom;
}
