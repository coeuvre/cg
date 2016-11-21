include_directories(${cg_SOURCE_DIR}/include)
include_directories(${cg_SOURCE_DIR}/src)

add_library(platform
    core/log.c)

set(cg_windows_SOURCES
    entry.c
    utils.c)

add_executable(cg_windows WIN32 ${cg_windows_SOURCES})
set_target_properties(cg_windows PROPERTIES OUTPUT_NAME cg)
target_link_libraries(cg_windows opengl32)
