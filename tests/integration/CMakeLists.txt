add_executable(integraion_tests
        ${CMAKE_SOURCE_DIR}/tests/integration/main.cpp
        )

target_link_libraries(integraion_tests gtest gtest_main Threads::Threads)