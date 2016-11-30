add_subdirectory(platform)

add_library(core
    log.c
    memory.c
    string.c)

target_link_libraries(core core_platform)
