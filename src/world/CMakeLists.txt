add_subdirectory(state)
add_subdirectory(generator)

add_library(world
        Engine.cpp Engine.h
        )

target_link_libraries(world state common generator)