#include <cg/core/utils.h>

#include <mach/mach_time.h>

CGu64 cgGetTicks(void)
{
    return mach_absolute_time();
}

CGu64 cgTicksToNanoseconds(CGu64 ticks)
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

    return ticks * base.numer / base.denom;
}
