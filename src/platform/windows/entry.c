#include "core/types.h"
#include "core/utils.h"
#include "platform/platform.h"

#include <stdio.h>
#include <Windows.h>

#define WINDOW_CLASS_NAME "CG_WINDOW_CLASS"

void cg_log(LogLevel level, char *format, ...)
{
    (void)level;
    va_list args;
    va_start(args, format);

    char buf[512];
    _vsnprintf_s(buf, 512, 511, format, args);
    buf[511] = 0;
    OutputDebugString(buf);

    va_end(args);
}

// If the function succeeds, the return value is the length of the string that
// is copied to the buffer, in characters, not including the terminating null
// character. If the buffer is too small to hold the string, the string is
// truncated to `size` characters including the terminating null character,
// the function returns `size`
static u32 get_executable_dir(char *buf, u32 size)
{
    u32 len = GetModuleFileName(NULL, buf, size);
    if (len == size) {
        // The buf is too small, we cannot get the entire path
        return size;
    } else {
        // Change the last `\\` to `\0`
        char *p = buf + len - 1;
        while (p > buf && *p != 0) {
            if (*p == '\\') {
                *p = 0;
                break;
            }
            --p;
        }
        return (u32)(p - buf);
    }
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

    PlatformApi platform = {
        .log = cg_log,
    };
    (void)platform;

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

    HWND hwnd = CreateWindowEx(0, WINDOW_CLASS_NAME,
                               "CG",
                               WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT,
                               CW_USEDEFAULT, CW_USEDEFAULT,
                               0, 0,
                               hinstance,
                               NULL);

    if (hwnd == 0) {
        LOG_ERROR("Failed to create window.\n");
        return -1;
    }

    ShowWindow(hwnd, SW_SHOW);

    char buf[512];
    get_executable_dir(buf, ARRAY_COUNT(buf));
    LOG_INFO("Executable Path: %s\n", buf);

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
