

add_executable(marble-light main.cpp)

target_link_libraries(marble-light PRIVATE raytracer)
target_include_directories(marble-light PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)