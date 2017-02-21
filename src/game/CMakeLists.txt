add_subdirectory(platform)

add_library(CGGame
    game.c)

target_link_libraries(CGGame CGGamePlatform)
