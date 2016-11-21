add_library(platform
    core/log.c)

add_library(entry
    entry.c
    util.c)

target_link_libraries(entry opengl32)

#set_target_properties(cg_windows PROPERTIES OUTPUT_NAME cg)
