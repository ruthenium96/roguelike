find_package(GTest)
IF(GTest_FOUND)
    include_directories(${GTest_INCLUDE_DIRS})
ELSE()
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        "release-1.11.0"
    )
    FetchContent_MakeAvailable(googletest)
    include_directories(${CMAKE_SOURCE_DIR}/libs/googletest/googletest/include)
ENDIF()

add_subdirectory(unit)