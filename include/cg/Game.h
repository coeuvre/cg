#ifndef CG_GAME_H
#define CG_GAME_H

#include <cg/Core.h>

typedef void CGInitGameFn(void *userData);
typedef void CGUpdateGameFn(void *userData, CGf32 dt);
typedef void CGRenderGameFn(void *userData);
typedef void CGTermGameFn(void *userData);

void cgOnInitGame(CGInitGameFn *init);
void cgOnUpdateGame(CGUpdateGameFn *update);
void cgOnRenderGame(CGRenderGameFn *render);
void cgOnTermGame(CGTermGameFn *term);

void cgRunGame(void *userData);

#endif // CG_GAME_H
