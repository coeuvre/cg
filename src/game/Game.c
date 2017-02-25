#include "game/Game.h"

CGInitGameFn *CG_INIT_GAME;
CGUpdateGameFn *CG_UPDATE_GAME;
CGRenderGameFn *CG_RENDER_GAME;
CGTermGameFn *CG_TERM_GAME;

void cgOnInitGame(CGInitGameFn *init)
{
    CG_INIT_GAME = init;
}

void cgOnUpdateGame(CGUpdateGameFn *update)
{
    CG_UPDATE_GAME = update;
}

void cgOnRenderGame(CGRenderGameFn *render)
{
    CG_RENDER_GAME = render;
}

void cgOnTermGame(CGTermGameFn *term)
{
    CG_TERM_GAME = term;
}
