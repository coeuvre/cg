#add_subdirectory(platform/windows)
add_subdirectory(core)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#if (WIN32)
    #set(CMAKE_SHARED_LIBRARY_PREFIX "")
#endif()

#add_library(cg SHARED cg.c)
