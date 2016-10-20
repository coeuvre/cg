#include "core/types.h"
#include "core/utils.h"

#define LOG_ERROR(format, ...) platform_log(LogLevel_Error, format, __VA_ARGS__)
#define LOG_WARN(format, ...) platform_log(LogLevel_Warn, format, __VA_ARGS__)
#define LOG_INFO(format, ...) platform_log(LogLevel_Info, format, __VA_ARGS__)
#define LOG_DEBUG(format, ...) platform_log(LogLevel_Debug, format, __VA_ARGS__)
#define LOG_TRACE(format, ...) platform_log(LogLevel_Trace, format, __VA_ARGS__)

#include <stdio.h>
#include <Windows.h>

#define WINDOW_CLASS_NAME "CG_WINDOW_CLASS"

static void platform_log(LogLevel level, char *format, ...)
{
    (void)level;
    va_list args;
    va_start(args, format);

    char buf[512];
    _vsnprintf_s(buf, 512, 511, format, args);
    buf[511] = 0;
    OutputDebugStringA(buf);

    va_end(args);
}

static LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
        case WM_KEYDOWN: {
            i32 key = (i32)wparam;
            if (key == VK_ESCAPE) {
                PostQuitMessage(0);
            }
        } break;

        case WM_CLOSE: {
            PostQuitMessage(0);
            LOG_TRACE("WM_CLOSE\n");
        } break;

        case WM_DESTROY: {
            LOG_TRACE("WM_DESTROY\n");
            ASSERT(false);
        }

        default: return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return 0;
}

int CALLBACK WinMain(HINSTANCE hinstance, HINSTANCE prev_hinstance, LPSTR cmd, int show)
{
    (void)prev_hinstance;
    (void)cmd;
    (void)show;

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = window_proc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hInstance = hinstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;

    if (RegisterClassEx(&wc) == 0) {
        LOG_ERROR("Failed to register window class.\n");
        return -1;
    }

    HWND hwnd = CreateWindowExA(0, WINDOW_CLASS_NAME,
                                "CG",
                                WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                0, 0,
                                hinstance,
                                NULL);

    if (hwnd == 0) {
        LOG_ERROR("Failed to create window.\n");
    }

    ShowWindow(hwnd, SW_SHOW);

    for (;;) {
        bool running = true;

        MSG msg = {0};
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
                break;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        if (!running) {
            break;
        }
    }

    return 0;
}
