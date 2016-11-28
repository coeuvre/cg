#include <OpenGL/gl.h>

#include <cg/core.h>
#include <cg/game/lifecycle.h>

struct cg_game_state {
    size_t size;
};

struct cg_game_state *cg_game_startup(void)
{
    cg_debug("STARTUP");

    size_t size = sizeof(struct cg_game_state);
    struct cg_game_state *state = cg_alloc(size);
    state->size = size;

    return state;
}

void cg_game_started(struct cg_game_state *state)
{
    cg_debug("STARTED");
}

void cg_game_shutdown(struct cg_game_state *state)
{
    cg_debug("SHUTDOWN");

    cg_free(state, state->size);
}

void cg_game_update(struct cg_game_state *state, float dt)
{
    cg_debug("UPDATE");
    cg_debug("dt: %f", dt);
}

void cg_game_render(struct cg_game_state *state)
{
    cg_debug("RENDER");

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(  0.0,  0.6, 0.0);
        glVertex3f( -0.2, -0.3, 0.0);
        glVertex3f(  0.2, -0.3 ,0.0);
    }
    glEnd();
    glFlush();
}
