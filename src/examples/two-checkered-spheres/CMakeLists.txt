
add_executable(two-checkered-spheres main.cpp)
target_link_libraries(two-checkered-spheres PRIVATE raytracer)
target_include_directories(two-checkered-spheres PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)