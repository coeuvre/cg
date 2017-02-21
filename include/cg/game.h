#ifndef CG_GAME_H
#define CG_GAME_H

#include <cg/Core.h>

typedef void CGGameInitFn(void *userData);
typedef void CGGameUpdateFn(void *userData, CGf32 dt);
typedef void CGGameRenderFn(void *userData);
typedef void CGGameTermFn(void *userData);

void cgOnGameInit(CGGameInitFn *init);
void cgOnGameUpdate(CGGameUpdateFn *update);
void cgOnGameRender(CGGameRenderFn *render);
void cgOnGameTerm(CGGameTermFn *term);

void cgRunGame(void *userData);

#endif // CG_GAME_H
