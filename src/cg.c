#include "core/core.h"
#include "platform/platform.h"

cgPlatformState *CG_PLATFORM;

typedef struct GameState {
    size_t size;
} GameState;

CG_LOG(cg_log)
{
    va_list args;
    va_start(args, format);
    CG_PLATFORM->api.vlog(level, format, args);
    va_end(args);
}

CG_EXPORT CG_LOADED(cg_loaded)
{
    CG_PLATFORM = state;

    if (state->data == 0) {
        size_t size = cg_size_mb(128);
        GameState *game_state = state->data = state->api.memory.alloc(size);
        game_state->size = size;
    }

    cg_info("Game Loaded!\n");
}

CG_EXPORT CG_UPDATE(cg_update)
{
    cg_info("dt: %f\n", dt);

    GameState *state = CG_PLATFORM->data;
}
