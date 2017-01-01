#include <cg/core.h>
#include <cg/game.h>

#include "game/game.h"

#include <Windows.h>
#include <GL/GL.h>
#include <stdio.h>

#define WINDOW_CLASS_NAME "CG_WINDOW_CLASS"

static LRESULT CALLBACK window_proc(HWND hwnd, UINT msg,
                                    WPARAM wparam, LPARAM lparam)
{
    int32_t key = (int32_t)wparam;

    switch (msg) {
    case WM_KEYDOWN:
        if (key == VK_ESCAPE) {
            PostQuitMessage(0);
        }
        break;

    case WM_CLOSE:
        PostQuitMessage(0);
        CG_LOG(DEBUG, "WM_CLOSE");
        break;

    case WM_DESTROY:
        CG_LOG(DEBUG, "WM_DESTROY");
        CG_ASSERT(false);
        break;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

struct frame_context {
    void *userdata;
    HDC hdc;
    int64_t last_frame_start;
    float frametime;
};

/*
 * TODO: The gap between two frames is not stable even the frame cost is low.
 *       Find a way to fix this.
 */
static void do_one_frame(struct frame_context *context)
{
    uint64_t frametime_ns = cg_s2ns(context->frametime);

    uint64_t frame_start = cg_current_counter();

    if (CG_GAME_UPDATE) {
        CG_GAME_UPDATE(context->userdata, context->frametime);
    }

    if (CG_GAME_RENDER) {
        CG_GAME_RENDER(context->userdata);
    }

    uint64_t frame_end = cg_current_counter();
    uint64_t frame_cost = cg_counter2ns(frame_end - frame_start);
    frame_cost = cg_ns2ms(frame_cost);
    CG_LOG(DEBUG, "Frame Cost: %"PRId64"ms", frame_cost);

    SwapBuffers(context->hdc);

    frame_end = cg_current_counter();
    uint64_t elapsed = cg_counter2ns(frame_end - frame_start);

    if (elapsed < frametime_ns) {
        uint32_t t = (uint32_t)cg_ns2ms(frametime_ns - elapsed);
        CG_LOG(DEBUG, "Sleep for %d ms", t);
        Sleep(t);
    }
}

void cg_run_game(void *userdata)
{
    timeBeginPeriod(1);

    HINSTANCE hinstance = GetModuleHandle(NULL);

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    /*
     * For OpenGL:
     *
     * When you create your HWND, you need to make sure that it has the CS_OWNDC
     * set for its style.
     */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = window_proc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hInstance = hinstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;

    if (RegisterClassEx(&wc) == 0) {
        CG_LOG(ERROR, "Failed to register window class.");
        return;
    }

    HWND hwnd = CreateWindowEx(0, WINDOW_CLASS_NAME,
                               "CG",
                               WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT,
                               CW_USEDEFAULT, CW_USEDEFAULT,
                               0, 0,
                               hinstance,
                               NULL);

    if (hwnd == 0) {
        CG_LOG(ERROR, "Failed to create window.");
        return;
    }

    HDC hdc = GetDC(hwnd);
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, /* Flags */
        PFD_TYPE_RGBA, /* The kind of framebuffer. RGBA or palette. */
        32, /* Colordepth of the framebuffer. */
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24, /* Number of bits for the depthbuffer */
        8, /* Number of bits for the stencilbuffer */
        0, /* Number of Aux buffers in the framebuffer. */
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };
    int pfi = ChoosePixelFormat(hdc, &pfd);
    if (pfi == 0) {
        CG_LOG(ERROR, "Failed to choose pixel format.");
        return;
    }

    if (SetPixelFormat(hdc, pfi, &pfd) == FALSE) {
        CG_LOG(ERROR, "Failed to set pixel format.");
        return;
    }

    HGLRC hglrc = wglCreateContext(hdc);
    if (hglrc == NULL) {
        CG_LOG(ERROR, "Failed to create OpenGL context.");
        return;
    }

    if (wglMakeCurrent(hdc, hglrc) == FALSE) {
        CG_LOG(ERROR, "Failed to make current OpenGL context.");
        return;
    }

    CG_LOG(INFO, "OpenGL Version: %s", glGetString(GL_VERSION));

    if (CG_GAME_INIT) {
        CG_GAME_INIT(userdata);
    }

    ShowWindow(hwnd, SW_SHOW);

    struct frame_context context = {
        .userdata = userdata,
        .hdc = hdc,
        .last_frame_start = 0,
        .frametime = 0.016667f,
    };

    bool running = true;
    MSG msg;
    while (running) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            do_one_frame(&context);
        }
    }

    if (CG_GAME_TERM) {
        CG_GAME_TERM(userdata);
    }
}
