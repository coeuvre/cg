#ifndef CG_GAME_GAME_H
#define CG_GAME_GAME_H

#include <cg/game.h>

extern CGGameInitFn *CG_GAME_INIT;
extern CGGameUpdateFn *CG_GAME_UDPATE;
extern CGGameRenderFn *CG_GAME_RENDER;
extern CGGameTermFn *CG_GAME_TERM;

#endif // CG_GAME_GAME_H
