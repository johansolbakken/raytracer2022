

add_executable(empty-cornell main.cpp)

target_link_libraries(empty-cornell PRIVATE raytracer)
target_include_directories(empty-cornell PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)