
add_executable(montecarlo main.cpp)

target_link_libraries(montecarlo PRIVATE raytracer)
target_include_directories(montecarlo PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)