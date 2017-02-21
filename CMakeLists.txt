cmake_minimum_required(VERSION 3.0)

project(libcg VERSION 0.1)

include_directories(${libcg_SOURCE_DIR}/include)
include_directories(${libcg_SOURCE_DIR}/src)

add_subdirectory(src)

enable_testing()
add_subdirectory(test/core)
