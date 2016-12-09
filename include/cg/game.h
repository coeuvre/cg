#ifndef CG_GAME_H
#define CG_GAME_H

typedef void cg_game_init_fn(void *userdata);
typedef void cg_game_update_fn(void *userdata, float dt);
typedef void cg_game_render_fn(void *userdata);
typedef void cg_game_term_fn(void *userdata);

void cg_on_game_init(cg_game_init_fn *init);
void cg_on_game_update(cg_game_update_fn *update);
void cg_on_game_render(cg_game_render_fn *render);
void cg_on_game_term(cg_game_term_fn *term);

void cg_run_game(void *userdata);

#endif /* CG_GAME_H */
