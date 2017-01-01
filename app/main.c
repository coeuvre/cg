#include <cg/core.h>
#include <cg/game.h>

#ifdef CG_PLATFORM_WINDOWS
#include <Windows.h>
#include <GL/gl.h>
#elif CG_PLATFORM_MACOS
#include <OpenGL/gl.h>
#endif

struct game_state {
    int64_t last_counter;
};

static void init(void *userdata)
{
    CG_LOG(DEBUG, "INIT");
}

static void term(void *userdata)
{
    CG_LOG(DEBUG, "TERM");
}

static void update(void *userdata, float dt)
{
    CG_LOG(DEBUG, "UPDATE");

    struct game_state *state = userdata;

    uint64_t current_count = cg_current_counter();
    if (state->last_counter != 0) {
        uint64_t nanosec =
            cg_counter2ns(current_count - state->last_counter);
        uint64_t millisec = cg_ns2ms(nanosec);
        CG_LOG(DEBUG, "Frame Gap: %"PRId64"ms", millisec);
    }
    state->last_counter = current_count;
}

static void render(void *userdata)
{
    CG_LOG(DEBUG, "RENDER");

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
