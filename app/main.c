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
    cg_debug("INIT");
}

static void term(void *userdata)
{
    cg_debug("TERM");
}

static void update(void *userdata, float dt)
{
    cg_debug("UPDATE");

    struct game_state *state = userdata;

    int64_t current_count = cg_get_current_counter();
    if (state->last_counter != 0) {
        int64_t nanosec =
            cg_counter_to_nanosec(current_count - state->last_counter);
        int64_t millisec = cg_nanosec_to_millisec(nanosec);
        cg_debug("Frame Gap: %"PRId64"ms", millisec);
    }
    state->last_counter = current_count;
}

static void render(void *userdata)
{
    cg_debug("RENDER");

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
    cg_set_log_level(CG_LOG_LEVEL_DEBUG);

    struct cg_game_lifecycle lifecycle = {
        .init   = &init,
        .term   = &term,
        .update = &update,
        .render = &render,

    };

    struct game_state state = {0};

    struct cg_game_config config = {
        .lifecycle = &lifecycle,
        .userdata  = &state,
    };

    cg_run_game(&config);

    return 0;
}
