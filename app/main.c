#include <cg/core.h>
#include <cg/game.h>

#ifdef CG_PLATFORM_WINDOWS
#include <Windows.h>
#include <GL/gl.h>
#elif CG_PLATFORM_MACOS
#include <OpenGL/gl.h>
#endif

typedef struct GameState {
    CGu64 lastTicks;
} GameState;

static void init(void *userData)
{
    cgLog(DEBUG, "INIT");
}

static void term(void *userData)
{
    cgLog(DEBUG, "TERM");
}

static void update(void *userData, float dt)
{
    cgLog(DEBUG, "UPDATE");

    GameState *state = userData;

    CGu64 ticks = cgGetTicks();
    if (state->lastTicks != 0) {
        CGu64 ns = cgTicksToNanoseconds(ticks - state->lastTicks);
        CGu64 ms = cgNanosecondsToMilliseconds(ns);
        cgLog(DEBUG, "Frame Gap: %"PRId64"ms", ms);
    }
    state->lastTicks = ticks;
}

static void render(void *userData)
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

    GameState state = {0};

    cgRunGame(&state);

    return 0;
}
