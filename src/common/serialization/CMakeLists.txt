MESSAGE(STATUS "Generating protobuf files.")

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

set(SERIALIZATION_FOLDER_PATH ${PROJECT_SOURCE_DIR}/src/common/serialization)

# TODO: handle non zero return code

execute_process(
        COMMAND protoc -I=${SERIALIZATION_FOLDER_PATH}/proto/ --cpp_out=${SERIALIZATION_FOLDER_PATH}/proto/ ${SERIALIZATION_FOLDER_PATH}/proto/state.proto
        RESULT_VARIABLE _EXIT_CODE)

add_library(serializer
        serialization.cpp
        serialization.h)

target_link_libraries(world common state)