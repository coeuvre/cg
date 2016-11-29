add_library(game game.m)

target_compile_options(game PRIVATE "-fobjc-arc")
target_link_libraries(game core platform)
