#include <Windows.h>
#include <GL/GL.h>
#include <stdio.h>

#include <cg/core/log.h>
#include <cg/core/string.h>
#include <cg/core/util.h>

#include <cg/game/life_cycle.h>

#include "platform/windows/util.h"

#define WINDOW_CLASS_NAME "CG_WINDOW_CLASS"

/*
typedef struct GameCode {
    HMODULE dll;
    FILETIME dll_last_write_time;

    cgLoaded *loaded;
    cgUpdate *update;

    bool is_valid;
} GameCode;

static GameCode
load_game_code(char *dll_filename, char *dll_temp_filename)
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

static void
unload_game_code(GameCode *game_code)
{
    if (game_code->dll) {
        FreeLibrary(game_code->dll);
    }

    game_code->is_valid = false;
}
*/

static LRESULT CALLBACK
window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
        case WM_KEYDOWN: {
            int32_t key = (int32_t)wparam;
            if (key == VK_ESCAPE) {
                PostQuitMessage(0);
            }
        } break;

        case WM_CLOSE: {
            PostQuitMessage(0);
            cg_debug("WM_CLOSE");
        } break;

        case WM_DESTROY: {
            cg_debug("WM_DESTROY");
            cg_assert(false);
        }

        default: return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return 0;
}

int CALLBACK
WinMain(HINSTANCE hinstance, HINSTANCE prev_hinstance, LPSTR cmd, int show)
{
    (void)prev_hinstance;
    (void)cmd;
    (void)show;

    cg_info("size_t: %d", sizeof(size_t));
    cg_info("uint64_t: %d", sizeof(uint64_t));
    cg_info("uint32_t: %d", sizeof(uint32_t));
    cg_info("double: %d", sizeof(double));
    cg_info("float: %d", sizeof(float));

    /*
    cgPlatformState state = {
        .api = {
            .vlog = cg_vlog,
            .memory = {
                .alloc = cg_alloc,
                .free = cg_free,
            },
        }
    };
    */

    /*
    char exectuable_dir[MAX_PATH];
    size_t exectuable_dir_size = get_executable_dir(exectuable_dir, cg_array_count(exectuable_dir));
    cg_info("Executable directory: %s", exectuable_dir);

    char exectuable_name[MAX_PATH];
    size_t exectuable_name_size = get_executable_name(exectuable_name, cg_array_count(exectuable_name));

    char dll_name[MAX_PATH];
    size_t dll_name_size = cg_cstr_copy(dll_name, cg_array_count(dll_name), exectuable_name);
    {
        size_t p = cg_cstr_rfind(dll_name, '.');
        if (p != CG_INVALID_INDEX) {
            char ext[] = ".dll";
            dll_name_size = cg_cstr_copy(dll_name + p,
                                         cg_array_count(dll_name) - p, ext);
        } else {
            cg_assert(!"Bad executable name");
        }
    }

    char dll_fullpath[MAX_PATH];
    cg_str_concat(dll_fullpath, cg_array_count(dll_fullpath),
                  exectuable_dir, exectuable_dir_size, dll_name, dll_name_size);
    cg_info("DLL name: %s", dll_fullpath);

    char dll_temp_name[512];
    size_t dll_temp_name_size = cg_str_copy(dll_temp_name, cg_array_count(dll_temp_name),
                                            exectuable_name, exectuable_name_size);
    {
        char *p = cg_str_rfind(dll_temp_name, dll_temp_name_size, '.');
        if (p) {
            char ext[] = "_temp.dll";
            dll_temp_name_size = cg_str_push(dll_temp_name, cg_array_count(dll_temp_name),
                                             p - dll_temp_name,
                                             ext, cg_array_count(ext) - 1);
        } else {
            assert(!"Bad executable name");
        }
    }

    char dll_temp_fullpath[MAX_PATH];
    cg_str_concat(dll_temp_fullpath, cg_array_count(dll_temp_fullpath),
                  exectuable_dir, exectuable_dir_size, dll_temp_name, dll_temp_name_size);
    cg_info("DLL temp name: %s", dll_temp_fullpath);
    */

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
        cg_error("Failed to register window class.");
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
        cg_error("Failed to create window.");
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
        cg_error("Failed to choose pixel format.");
        return -1;
    }

    if (SetPixelFormat(hdc, pfi, &pfd) == FALSE) {
        cg_error("Failed to set pixel format.");
        return -1;
    }

    HGLRC hglrc = wglCreateContext(hdc);
    if (hglrc == NULL) {
        cg_error("Failed to create OpenGL context.");
        return -1;
    }

    if (wglMakeCurrent(hdc, hglrc) == FALSE) {
        cg_error("Failed to make current OpenGL context.");
        return -1;
    }

    cg_info("OpenGL Version: %s", glGetString(GL_VERSION));

    /*
    GameCode game_code = load_game_code(dll_fullpath, dll_temp_fullpath);
    if (game_code.is_valid) {
        game_code.loaded(&state);
    }

    assert(game_code.is_valid);
    */

    cg_game_init();

    ShowWindow(hwnd, SW_SHOW);

    float frame_time = 0.016667f;
    float elapsed_time = frame_time; // The first frame can start immediately
    int64_t last_counter = get_current_counter();
    int64_t current_counter = last_counter;

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

        /*
        FILETIME new_dll_last_write_time = get_last_write_time(dll_fullpath);
        if (CompareFileTime(&new_dll_last_write_time, &game_code.dll_last_write_time) != 0) {
            unload_game_code(&game_code);
            game_code = load_game_code(dll_fullpath, dll_temp_fullpath);
            if (game_code.is_valid) {
                game_code.loaded(&state);
            }
        }
        */

        current_counter = get_current_counter();
        elapsed_time += get_seconds_elapsed(last_counter, current_counter);
        last_counter = current_counter;
        cg_debug("Before frame, elapsed_time: %f", elapsed_time);

        if (elapsed_time >= frame_time) {
            elapsed_time -= frame_time;

            int64_t frame_start = get_current_counter();

            /*
            if (game_code.is_valid) {
                game_code.update(frame_time);
            }
            */

            cg_game_update(frame_time);
            cg_game_render();

            SwapBuffers(hdc);

            int64_t frame_end = get_current_counter();
            float frame_cost = get_seconds_elapsed(frame_start, frame_end);
            cg_debug("Frame cost: %f", frame_cost);
        }

        current_counter = get_current_counter();
        elapsed_time += get_seconds_elapsed(last_counter, current_counter);
        last_counter = current_counter;
        cg_debug("After frame, elapsed_time: %f", elapsed_time);

        if (frame_time > elapsed_time) {
            uint32_t remaining = (uint32_t)((frame_time - elapsed_time) * 1000.0f);
            cg_debug("Sleep for %d ms", remaining);
            Sleep(remaining);
        }
    }

    return 0;
}
