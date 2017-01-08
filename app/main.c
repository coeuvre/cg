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
    cgLog(DEBUG, "INIT");
}

static void term(void *userdata)
{
    cgLog(DEBUG, "TERM");
}

static void update(void *userdata, float dt)
{
    cgLog(DEBUG, "UPDATE");

    struct game_state *state = userdata;

    uint64_t current_count = cgGetTick();
    if (state->last_counter != 0) {
        uint64_t nanosec =
            cgTickToNanosecond(current_count - state->last_counter);
        uint64_t millisec = cgNanosecondToMillisecond(nanosec);
        cgLog(DEBUG, "Frame Gap: %"PRId64"ms", millisec);
    }
    state->last_counter = current_count;
}

static void render(void *userdata)
{
    cgLog(DEBUG, "RENDER");

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
    cgSetLogLevel(CG_LOG_LEVEL_DEBUG);

    cgOnGameInit(&init);
    cgOnGameUpdate(&update);
    cgOnGameRender(&render);
    cgOnGameTerm(&term);

    struct game_state state = {0};

    cgRunGame(&state);

    return 0;
}
