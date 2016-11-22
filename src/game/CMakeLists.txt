add_executable(game WIN32
    main.c)

target_link_libraries(game core platform entry)
