add_executable(test_core_string string.c)
target_link_libraries(test_core_string CGCore)
add_test(core/string test_core_string)
