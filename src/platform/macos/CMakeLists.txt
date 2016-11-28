add_library(platform
    core/log.c
    entry.m)
find_library(cocoa_framework Cocoa)
find_library(opengl_framework OpenGL)
find_library(core_video_framework CoreVideo)
target_link_libraries(platform
    ${cocoa_framework}
    ${opengl_framework}
    ${core_video_framework})
target_compile_options(platform PRIVATE "-fobjc-arc")
