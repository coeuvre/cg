add_subdirectory(platform)

add_library(game
    placeholder.c)

target_link_libraries(game game_platform)
