#include <cg/core.h>
#include <cg/game.h>

#include "game/Game.h"

#include <Windows.h>
#include <GL/GL.h>
#include <stdio.h>

#define WINDOW_CLASS_NAME "CG_WINDOW_CLASS"

static LRESULT CALLBACK windowProc(HWND hwnd, UINT msg,
                                   WPARAM wparam, LPARAM lparam)
{
    CGi32 key = (CGi32)wparam;

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

    default: break;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

typedef struct FrameContext {
    void *userData;
    HDC hdc;
    CGu64 lastFrameStart;
    CGf32 frameTime;
} FrameContext;

/*
 * TODO: The gap between two frames is not stable even the frame cost is low.
 *       Find a way to fix this.
 */
static void doOneFrame(FrameContext *context)
{
    CGu64 frameTimeNS = cgSecondsToNanoseconds(context->frameTime);

    CGu64 frameStart = cgGetTicks();

    if (CG_GAME_UDPATE) {
        CG_GAME_UDPATE(context->userData, context->frameTime);
    }

    if (CG_GAME_RENDER) {
        CG_GAME_RENDER(context->userData);
    }

    CGu64 frameEnd = cgGetTicks();
    CGu64 frameCost = cgTicksToNanoseconds(frameEnd - frameStart);
    frameCost = cgNanosecondsToMilliseconds(frameCost);
    cgLog(DEBUG, "Frame Cost: %"PRId64"ms", frameCost);

    SwapBuffers(context->hdc);

    frameEnd = cgGetTicks();
    CGu64 elapsed = cgTicksToNanoseconds(frameEnd - frameStart);

    if (elapsed < frameTimeNS) {
        CGu32 t = (CGu32)cgNanosecondsToMilliseconds(frameTimeNS - elapsed);
        cgLog(DEBUG, "Sleep for %d ms", t);
        Sleep(t);
    }
}

void cgRunGame(void *userData)
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
    wc.lpfnWndProc = windowProc;
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
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
        PFD_TYPE_RGBA, // The kind of framebuffer. RGBA or palette
        32, // Colordepth of the framebuffer
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24, // Number of bits for the depthbuffer
        8, // Number of bits for the stencilbuffer
        0, // Number of Aux buffers in the framebuffer.
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
        CG_GAME_INIT(userData);
    }

    ShowWindow(hwnd, SW_SHOW);

    FrameContext context = {
        .userData = userData,
        .hdc = hdc,
        .lastFrameStart = 0,
        .frameTime = 0.016667f,
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
            doOneFrame(&context);
        }
    }

    if (CG_GAME_TERM) {
        CG_GAME_TERM(userData);
    }
}
