#ifndef CG_GAME_LIFECYCLE_H
#define CG_GAME_LIFECYCLE_H

struct cg_game_state;

struct cg_game_state *cg_game_startup(void);

void cg_game_started(struct cg_game_state *state);

void cg_game_shutdown(struct cg_game_state *state);

void cg_game_update(struct cg_game_state *state, float dt);

void cg_game_render(struct cg_game_state *state);

#endif /* CG_GAME_LIFECYCLE_H */
