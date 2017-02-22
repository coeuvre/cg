#include "game/Game.h"

CGGameInitFn *CG_GAME_INIT;
CGGameUpdateFn *CG_GAME_UDPATE;
CGGameRenderFn *CG_GAME_RENDER;
CGGameTermFn *CG_GAME_TERM;

void cgOnGameInit(CGGameInitFn *init)
{
    CG_GAME_INIT = init;
}

void cgOnGameUpdate(CGGameUpdateFn *update)
{
    CG_GAME_UDPATE = update;
}

void cgOnGameRender(CGGameRenderFn *render)
{
    CG_GAME_RENDER = render;
}

void cgOnGameTerm(CGGameTermFn *term)
{
    CG_GAME_TERM = term;
}
