

add_executable(focus-scene main.cpp)

target_link_libraries(focus-scene PRIVATE raytracer)
target_include_directories(focus-scene PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)