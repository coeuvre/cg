#include "game/game.h"

cg_game_init_fn *CGGAME_INIT;
cg_game_update_fn *CGGAME_UPDATE;
cg_game_render_fn *CGGAME_RENDER;
cg_game_term_fn *CGGAME_TERM;

void cg_on_game_init(cg_game_init_fn *init)
{
    CGGAME_INIT = init;
}

void cg_on_game_update(cg_game_update_fn *update)
{
    CGGAME_UPDATE = update;
}

void cg_on_game_render(cg_game_render_fn *render)
{
    CGGAME_RENDER = render;
}

void cg_on_game_term(cg_game_term_fn *term)
{
    CGGAME_TERM = term;
}
