

add_executable(noise main.cpp)

target_link_libraries(noise PRIVATE raytracer)
target_include_directories(noise PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)