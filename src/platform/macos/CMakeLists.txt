add_library(platform
    core/log.c
    entry.m)
find_library(cocoa_framework Cocoa)
find_library(opengl_framework OpenGL)
target_link_libraries(platform ${cocoa_framework} ${opengl_framework})
