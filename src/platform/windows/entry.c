#include "core/types.h"
#include "core/utils.h"
#include "core/string.h"
#include "platform/platform.h"

#include <stdio.h>
#include <Windows.h>
#include <GL/GL.h>

#include "platform/windows/utils.c"

#define WINDOW_CLASS_NAME "CG_WINDOW_CLASS"

typedef struct GameCode {
    HMODULE dll;
    FILETIME dll_last_write_time;

    cgLoaded *loaded;
    cgUpdate *update;

    bool is_valid;
} GameCode;

static GameCode load_game_code(char *dll_filename, char *dll_temp_filename)
{
    GameCode game_code = {0};

    game_code.dll_last_write_time = get_last_write_time(dll_filename);

    CopyFile(dll_filename, dll_temp_filename, FALSE);
    game_code.dll = LoadLibrary(dll_temp_filename);

    if (game_code.dll) {
        game_code.loaded = (cgLoaded *)GetProcAddress(game_code.dll, "cg_loaded");
        game_code.update = (cgUpdate *)GetProcAddress(game_code.dll, "cg_update");
        game_code.is_valid = game_code.update;
    }

    return game_code;
}

static void unload_game_code(GameCode *game_code)
{
    if (game_code->dll) {
        FreeLibrary(game_code->dll);
    }

    game_code->is_valid = false;
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

    LOG_INFO("usize: %d\n", sizeof(usize));
    LOG_INFO("u64: %d\n", sizeof(u64));
    LOG_INFO("u32: %d\n", sizeof(u32));
    LOG_INFO("f64: %d\n", sizeof(f64));
    LOG_INFO("f32: %d\n", sizeof(f32));

    PlatformState state = {
        .api = {
            .vlog = vlog,
            .memory = {
                .alloc = cg_alloc,
                .free = cg_free,
            },
        }
    };

    char exectuable_dir[MAX_PATH];
    usize exectuable_dir_size = get_executable_dir(exectuable_dir, ARRAY_COUNT(exectuable_dir));
    LOG_INFO("Executable directory: %s\n", exectuable_dir);

    char exectuable_name[MAX_PATH];
    usize exectuable_name_size = get_executable_name(exectuable_name, ARRAY_COUNT(exectuable_name));

    char dll_name[MAX_PATH];
    usize dll_name_size = copy_str(dll_name, ARRAY_COUNT(dll_name), exectuable_name, exectuable_name_size);
    {
        char *p = find_str_right(dll_name, dll_name_size, '.');
        if (p) {
            char ext[] = ".dll";
            dll_name_size = push_str(dll_name, ARRAY_COUNT(dll_name), p - dll_name,
                                     ext, ARRAY_COUNT(ext));
        } else {
            ASSERT(!"Bad executable name");
        }
    }

    char dll_fullpath[MAX_PATH];
    concat_str(dll_fullpath, ARRAY_COUNT(dll_fullpath),
               exectuable_dir, exectuable_dir_size, dll_name, dll_name_size);
    LOG_INFO("DLL name: %s\n", dll_fullpath);

    char dll_temp_name[512];
    usize dll_temp_name_size = copy_str(dll_temp_name, ARRAY_COUNT(dll_temp_name),
                                           exectuable_name, exectuable_name_size);
    {
        char *p = find_str_right(dll_temp_name, dll_temp_name_size, '.');
        if (p) {
            char ext[] = "_temp.dll";
            dll_temp_name_size = push_str(dll_temp_name, ARRAY_COUNT(dll_temp_name),
                                          p - dll_temp_name,
                                          ext, ARRAY_COUNT(ext) - 1);
        } else {
            ASSERT(!"Bad executable name");
        }
    }

    char dll_temp_fullpath[MAX_PATH];
    concat_str(dll_temp_fullpath, ARRAY_COUNT(dll_temp_fullpath),
               exectuable_dir, exectuable_dir_size, dll_temp_name, dll_temp_name_size);
    LOG_INFO("DLL temp name: %s\n", dll_temp_fullpath);

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    // For OpenGL:
    // When you create your HWND, you need to make sure that it has the CS_OWNDC set for its style.
    wc.style = CS_OWNDC;
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

    HDC hdc = GetDC(hwnd);
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        //Flags
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        //The kind of framebuffer. RGBA or palette.
        PFD_TYPE_RGBA,
        //Colordepth of the framebuffer.
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        //Number of bits for the depthbuffer
        24,
        //Number of bits for the stencilbuffer
        8,
        //Number of Aux buffers in the framebuffer.
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };
    int pfi = ChoosePixelFormat(hdc, &pfd);
    if (pfi == 0) {
        LOG_ERROR("Failed to choose pixel format.\n");
        return -1;
    }

    if (SetPixelFormat(hdc, pfi, &pfd) == FALSE) {
        LOG_ERROR("Failed to set pixel format.\n");
        return -1;
    }

    HGLRC hglrc = wglCreateContext(hdc);
    if (hglrc == NULL) {
        LOG_ERROR("Failed to create OpenGL context.\n");
        return -1;
    }

    if (wglMakeCurrent(hdc, hglrc) == FALSE) {
        LOG_ERROR("Failed to make current OpenGL context.\n");
        return -1;
    }

    LOG_INFO("OpenGL Version: %s\n", glGetString(GL_VERSION));

    GameCode game_code = load_game_code(dll_fullpath, dll_temp_fullpath);
    if (game_code.is_valid) {
        game_code.loaded(&state);
    }

    ASSERT(game_code.is_valid);

    ShowWindow(hwnd, SW_SHOW);

    f32 frame_time = 0.016667;
    f32 elapsed_time = frame_time; // The first frame can start immediately
    i64 last_counter = get_current_counter();
    i64 current_counter = last_counter;

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

        FILETIME new_dll_last_write_time = get_last_write_time(dll_fullpath);
        if (CompareFileTime(&new_dll_last_write_time, &game_code.dll_last_write_time) != 0) {
            unload_game_code(&game_code);
            game_code = load_game_code(dll_fullpath, dll_temp_fullpath);
            if (game_code.is_valid) {
                game_code.loaded(&state);
            }
        }

        current_counter = get_current_counter();
        elapsed_time += get_seconds_elapsed(last_counter, current_counter);
        last_counter = current_counter;
        LOG_TRACE("Before frame, elapsed_time: %f\n", elapsed_time);

        if (elapsed_time >= frame_time) {
            elapsed_time -= frame_time;

            i64 frame_start = get_current_counter();

            if (game_code.is_valid) {
                game_code.update(frame_time);
            }

            i64 frame_end = get_current_counter();
            f32 frame_cost = get_seconds_elapsed(frame_start, frame_end);
            LOG_TRACE("Frame cost: %f\n", frame_cost);
        }

        current_counter = get_current_counter();
        elapsed_time += get_seconds_elapsed(last_counter, current_counter);
        last_counter = current_counter;
        LOG_TRACE("After frame, elapsed_time: %f\n", elapsed_time);

        if (frame_time > elapsed_time) {
            u32 remaining = (u32)((frame_time - elapsed_time) * 1000.0f);
            LOG_TRACE("Sleep for %d ms\n", remaining);
            Sleep(remaining);
        }
    }

    return 0;
}
