MESSAGE(STATUS "Generating protobuf files.")

find_package(Protobuf)
IF(Protobuf_FOUND)
    include_directories(${Protobuf_INCLUDE_DIRS})
ELSE()
    include(FetchContent)
    FetchContent_Declare(
            protobuf
            GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
            GIT_TAG        "v3.20.1"
            SOURCE_SUBDIR cmake
    )
    set(protobuf_BUILD_TESTS OFF)
    FetchContent_MakeAvailable(protobuf)
    include_directories(${CMAKE_SOURCE_DIR}/libs/protobuf/protobuf/include)
    set(protobuf_BUILD_TESTS OFF)
ENDIF()

set(SERIALIZATION_FOLDER_PATH ${PROJECT_SOURCE_DIR}/src/common/serialization)

# TODO: handle non zero return code

execute_process(
        COMMAND protoc -I=${SERIALIZATION_FOLDER_PATH}/proto/ --cpp_out=${SERIALIZATION_FOLDER_PATH}/proto/ ${SERIALIZATION_FOLDER_PATH}/proto/state.proto
        RESULT_VARIABLE _EXIT_CODE)

add_library(serializer
        serialization.cpp
        serialization.h)

target_link_libraries(world common state)