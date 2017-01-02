#ifndef CGCORE_GAME_GAME_H
#define CGCORE_GAME_GAME_H

#include <cg/game.h>

extern cg_game_init_fn *CGGAME_INIT;
extern cg_game_update_fn *CGGAME_UPDATE;
extern cg_game_render_fn *CGGAME_RENDER;
extern cg_game_term_fn *CGGAME_TERM;

#endif /* CGCORE_GAME_GAME_H */
