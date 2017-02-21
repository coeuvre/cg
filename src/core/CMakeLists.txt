add_subdirectory(platform)

add_library(CGCore
    Log.c
    Memory.c
    String.c)

target_link_libraries(CGCore CGCorePlatform)
