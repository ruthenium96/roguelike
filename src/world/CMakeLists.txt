add_subdirectory(state)

add_library(world
        Engine.cpp Engine.h
        generator/AbstractGenerator.h
        generator/OnTheFly.cpp generator/OnTheFly.h
        )

target_link_libraries(world state)