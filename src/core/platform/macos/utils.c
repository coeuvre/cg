#include <cg/core/utils.h>

#include <mach/mach_time.h>

uint64_t cg_get_current_counter(void)
{
    return mach_absolute_time();
}

uint64_t cg_counter_to_nanosec(uint64_t counter)
{
    static mach_timebase_info_data_t base;

    if (base.denom == 0) {
        mach_timebase_info(&base);
    }

    return counter * base.numer / base.denom;
}
