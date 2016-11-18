add_subdirectory(platform/windows)

include_directories(${cg_SOURCE_DIR}/include/cg)

if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

add_library(cg SHARED cg.c)
