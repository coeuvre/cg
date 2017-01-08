#ifndef CG_GAME_H
#define CG_GAME_H

#include <cg/core.h>

typedef void CGGameInitFn(void *userdata);
typedef void CGGameUpdateFn(void *userdata, CGfloat dt);
typedef void CGGameRenderFn(void *userdata);
typedef void CGGameTermFn(void *userdata);

void cgOnGameInit(CGGameInitFn *init);
void cgOnGameUpdate(CGGameUpdateFn *update);
void cgOnGameRender(CGGameRenderFn *render);
void cgOnGameTerm(CGGameTermFn *term);

void cgRunGame(void *userdata);

#endif /* CG_GAME_H */
