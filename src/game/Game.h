#ifndef CG_GAME_GAME_H
#define CG_GAME_GAME_H

#include <cg/Game.h>

extern CGInitGameFn *CG_INIT_GAME;
extern CGUpdateGameFn *CG_UPDATE_GAME;
extern CGRenderGameFn *CG_RENDER_GAME;
extern CGTermGameFn *CG_TERM_GAME;

#endif // CG_GAME_GAME_H
