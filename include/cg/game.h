#ifndef CG_GAME_H
#define CG_GAME_H

struct cg_game_lifecycle {
    void (*init)(void *userdata);
    void (*update)(void *userdata, float dt);
    void (*render)(void *userdata);
    void (*term)(void *userdata);
};

struct cg_game_config {
    struct cg_game_lifecycle lifecycle;
    void *userdata;
};

void cg_run_game(struct cg_game_config *config);

#endif /* CG_GAME_H */
