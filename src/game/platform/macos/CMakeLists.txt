add_library(CGGamePlatform Game.m)

target_compile_options(CGGamePlatform PRIVATE "-fobjc-arc")

find_library(cocoa_framework Cocoa)
find_library(opengl_framework OpenGL)
find_library(core_video_framework CoreVideo)
target_link_libraries(CGGamePlatform
    ${cocoa_framework}
    ${opengl_framework}
    ${core_video_framework})
