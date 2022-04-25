set(TEST_NAME roguelike_unit_tests)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include/ ${gtest_SOURCE_DIR})

add_executable(${TEST_NAME} ${TEST_SRC_FILES})

target_link_libraries(${TEST_NAME} gtest gtest_main)
target_link_libraries(${TEST_NAME} world)
