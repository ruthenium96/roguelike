add_subdirectory(state)
add_subdirectory(generator)

add_library(world
        Engine.cpp Engine.h
        )

add_library(random
        RandomNumberGenerator.h)
set_target_properties(random PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(world state common generator)