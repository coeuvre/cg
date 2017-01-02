#include <cg/core.h>
#include <cg/game.h>

#ifdef CGPLATFORM_WINDOWS
#include <Windows.h>
#include <GL/gl.h>
#elif CGPLATFORM_MACOS
#include <OpenGL/gl.h>
#endif

struct game_state {
    int64_t last_counter;
};

static void init(void *userdata)
{
    CGLOG(DEBUG, "INIT");
}

static void term(void *userdata)
{
    CGLOG(DEBUG, "TERM");
}

static void update(void *userdata, float dt)
{
    CGLOG(DEBUG, "UPDATE");

    struct game_state *state = userdata;

    uint64_t current_count = cg_current_counter();
    if (state->last_counter != 0) {
        uint64_t nanosec =
            cg_counter2ns(current_count - state->last_counter);
        uint64_t millisec = cg_ns2ms(nanosec);
        CGLOG(DEBUG, "Frame Gap: %"PRId64"ms", millisec);
    }
    state->last_counter = current_count;
}

static void render(void *userdata)
{
    CGLOG(DEBUG, "RENDER");

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLES);
        glVertex3f( 0.0f,  0.6f, 0.0f);
        glVertex3f(-0.2f, -0.3f, 0.0f);
        glVertex3f( 0.2f, -0.3f, 0.0f);
    glEnd();
    glFlush();
}

int main(int argc, const char *argv[])
{
    cgSetLogLevel(CGLOG_LEVEL_DEBUG);

    cg_on_game_init(&init);
    cg_on_game_update(&update);
    cg_on_game_render(&render);
    cg_on_game_term(&term);

    struct game_state state = {0};

    cg_run_game(&state);

    return 0;
}
