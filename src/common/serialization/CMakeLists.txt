MESSAGE(STATUS "Generating protobuf files.")

set(SERIALIZATION_FOLDER_PATH ${PROJECT_SOURCE_DIR}/src/common/serialization)

# TODO: handle non zero return code

execute_process(
        COMMAND protoc -I=${SERIALIZATION_FOLDER_PATH}/proto/ --cpp_out=${SERIALIZATION_FOLDER_PATH}/proto/ ${SERIALIZATION_FOLDER_PATH}/proto/state.proto
        RESULT_VARIABLE _EXIT_CODE)

add_library(serializer
        serialization.cpp
        serialization.h
        proto/state.pb.cc
        proto/state.pb.h)

target_link_libraries(world common state)