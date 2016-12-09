#ifndef CG_CORE_GAME_GAME_H
#define CG_CORE_GAME_GAME_H

#include <cg/game.h>

extern cg_game_init_fn *CG_GAME_INIT;
extern cg_game_update_fn *CG_GAME_UPDATE;
extern cg_game_render_fn *CG_GAME_RENDER;
extern cg_game_term_fn *CG_GAME_TERM;

#endif /* CG_CORE_GAME_GAME_H */
