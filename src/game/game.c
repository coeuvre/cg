#include "game/game.h"

cg_game_init_fn *CG_GAME_INIT;
cg_game_update_fn *CG_GAME_UPDATE;
cg_game_render_fn *CG_GAME_RENDER;
cg_game_term_fn *CG_GAME_TERM;

void cg_on_game_init(cg_game_init_fn *init)
{
    CG_GAME_INIT = init;
}

void cg_on_game_update(cg_game_update_fn *update)
{
    CG_GAME_UPDATE = update;
}

void cg_on_game_render(cg_game_render_fn *render)
{
    CG_GAME_RENDER = render;
}

void cg_on_game_term(cg_game_term_fn *term)
{
    CG_GAME_TERM = term;
}
