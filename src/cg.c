#include "core/types.h"
#include "core/string.h"
#include "core/utils.h"
#include "platform/platform.h"

PlatformState *PLATFORM;

CG_LOG(cg_log)
{
    va_list args;
    va_start(args, format);
    PLATFORM->api.vlog(level, format, args);
    va_end(args);
}

CG_LOADED(cg_loaded)
{
    PLATFORM = state;

    if (state->data == 0) {
        state->data = state->api.memory.alloc(GB(2));
    }

    LOG_INFO("Loaded!\n");
}

CG_UPDATE(cg_update)
{
    LOG_INFO("dt: %f\n", dt);
}
