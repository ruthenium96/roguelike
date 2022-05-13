add_subdirectory(serialization)

add_library(generator
        AbstractGenerator.h AbstractGenerator.cpp
        OnTheFly.cpp OnTheFly.h
        FromTheDisk.cpp FromTheDisk.h GeneratorBuilder.cpp GeneratorBuilder.h)

target_link_libraries(generator serializer state random)