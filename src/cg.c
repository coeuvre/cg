#include "core/types.h"
#include "core/string.h"
#include "core/utils.h"
#include "platform/platform.h"

static PlatformApi *PLATFORM;

CG_LOG(cg_log)
{
    va_list args;
    va_start(args, format);
    PLATFORM->vlog(level, format, args);
    va_end(args);
}

CG_LOADED(cg_loaded)
{
    PLATFORM = platform;
}

CG_UPDATE(cg_update)
{
    LOG_INFO("dt: %f\n", dt);
}
