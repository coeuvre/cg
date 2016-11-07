add_subdirectory(platform/windows)

include_directories(${cg_SOURCE_DIR}/include/cg)

add_library(cg SHARED cg.c)
