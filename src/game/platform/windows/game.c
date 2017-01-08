#include <cg/core.h>
#include <cg/game.h>

#include "game/game.h"

#include <Windows.h>
#include <GL/GL.h>
#include <stdio.h>

#define WINDOW_CLASS_NAME "CGWINDOW_CLASS"

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
        cgLog(DEBUG, "WM_CLOSE");
        break;

    case WM_DESTROY:
        cgLog(DEBUG, "WM_DESTROY");
        cgAssert(false);
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
    uint64_t frametime_ns = cgSecondsToNanoseconds(context->frametime);

    uint64_t frame_start = cgGetTicks();

    if (CG_GAME_UDPATE) {
        CG_GAME_UDPATE(context->userdata, context->frametime);
    }

    if (CG_GAME_RENDER) {
        CG_GAME_RENDER(context->userdata);
    }

    uint64_t frame_end = cgGetTicks();
    uint64_t frame_cost = cgTicksToNanoseconds(frame_end - frame_start);
    frame_cost = cgNanosecondsToMilliseconds(frame_cost);
    cgLog(DEBUG, "Frame Cost: %"PRId64"ms", frame_cost);

    SwapBuffers(context->hdc);

    frame_end = cgGetTicks();
    uint64_t elapsed = cgTicksToNanoseconds(frame_end - frame_start);

    if (elapsed < frametime_ns) {
        uint32_t t = (uint32_t)cgNanosecondsToMilliseconds(frametime_ns - elapsed);
        cgLog(DEBUG, "Sleep for %d ms", t);
        Sleep(t);
    }
}

void cgRunGame(void *userdata)
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
        cgLog(ERROR, "Failed to register window class.");
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
        cgLog(ERROR, "Failed to create window.");
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
        cgLog(ERROR, "Failed to choose pixel format.");
        return;
    }

    if (SetPixelFormat(hdc, pfi, &pfd) == FALSE) {
        cgLog(ERROR, "Failed to set pixel format.");
        return;
    }

    HGLRC hglrc = wglCreateContext(hdc);
    if (hglrc == NULL) {
        cgLog(ERROR, "Failed to create OpenGL context.");
        return;
    }

    if (wglMakeCurrent(hdc, hglrc) == FALSE) {
        cgLog(ERROR, "Failed to make current OpenGL context.");
        return;
    }

    cgLog(INFO, "OpenGL Version: %s", glGetString(GL_VERSION));

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
