

add_executable(moving-spheres main.cpp)

target_link_libraries(moving-spheres PRIVATE raytracer)
target_include_directories(moving-spheres PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)