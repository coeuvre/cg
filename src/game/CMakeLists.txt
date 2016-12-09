add_subdirectory(platform)

add_library(game
    game.c)

target_link_libraries(game game_platform)
