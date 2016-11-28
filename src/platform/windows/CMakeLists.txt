add_library(platform
    core/log.c)

target_link_libraries(platform opengl32)

#set_target_properties(cg_windows PROPERTIES OUTPUT_NAME cg)
