add_library(game_platform game.m)

target_compile_options(game_platform PRIVATE "-fobjc-arc")

find_library(cocoa_framework Cocoa)
find_library(opengl_framework OpenGL)
find_library(core_video_framework CoreVideo)
target_link_libraries(game_platform
    ${cocoa_framework}
    ${opengl_framework}
    ${core_video_framework})
