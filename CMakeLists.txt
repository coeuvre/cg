cmake_minimum_required(VERSION 3.0)

project(cg VERSION 0.1)

include_directories(${cg_SOURCE_DIR}/include)
include_directories(${cg_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(app)

enable_testing()
add_subdirectory(test/core)
