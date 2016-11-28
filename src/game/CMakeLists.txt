add_library(game platform/windows/game.c)

target_link_libraries(game core platform)
