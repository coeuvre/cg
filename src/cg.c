#include "core/core.h"
#include "platform/platform.h"

PlatformState *PLATFORM;

typedef struct GameState {
    usize size;
} GameState;

LOG(log)
{
    va_list args;
    va_start(args, format);
    PLATFORM->api.vlog(level, format, args);
    va_end(args);
}

EXPORT
CG_LOADED(cg_loaded)
{
    PLATFORM = state;

    if (state->data == 0) {
        usize size = MB(128);
        GameState *game_state = state->data = state->api.memory.alloc(size);
        game_state->size = size;
    }

    info("Game Loaded!\n");
}

EXPORT
CG_UPDATE(cg_update)
{
    info("dt: %f\n", dt);

    GameState *state = PLATFORM->data;
}
