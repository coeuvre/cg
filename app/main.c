#include <cg/core.h>
#include <cg/game.h>

#ifdef CG_PLATFORM_WINDOWS
#include <Windows.h>
#include <GL/gl.h>
#elif CG_PLATFORM_MACOS
#include <OpenGL/gl.h>
#endif

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
}

static void render(void *userdata)
{
    cg_debug("RENDER");

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f( 0.0f,  0.6f, 0.0f);
        glVertex3f(-0.2f, -0.3f, 0.0f);
        glVertex3f( 0.2f, -0.3f, 0.0f);
    }
    glEnd();
    glFlush();
}

#if CG_PLATFORM_WINDOWS

int CALLBACK WinMain(HINSTANCE hinstance, HINSTANCE prev_hinstance,
                     LPSTR cmd, int show)
{
    struct cg_game_config config = {
        .lifecycle = {
            .init = &init,
            .term = &term,
            .update = &update,
            .render = &render,
        },

        .userdata = 0,
    };

    cg_run_game(&config);

    return 0;
}

#elif CG_PLATFORM_MACOS

int main(int argc, const char *argv[])
{
    struct cg_game_config config = {
        .lifecycle = {
            .init = &init,
            .term = &term,
            .update = &update,
            .render = &render,
        },

        .userdata = 0,
    };

    cg_run_game(&config);

    return 0;
}

#endif
