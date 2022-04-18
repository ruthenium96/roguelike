add_subdirectory(world)
add_subdirectory(ui)
add_subdirectory(controller)
add_subdirectory(common)

add_executable(main main.cpp)

target_link_libraries(main world controller ui)