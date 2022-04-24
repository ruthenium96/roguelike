add_executable(unit_tests
        ${CMAKE_SOURCE_DIR}/tests/unit/main.cpp
        ${CMAKE_SOURCE_DIR}/tests/unit/engine/state_tests.cpp
        )

target_link_libraries(unit_tests gtest gtest_main world Threads::Threads)