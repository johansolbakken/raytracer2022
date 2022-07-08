

add_executable(hollow-glass main.cpp)

target_link_libraries(hollow-glass PRIVATE raytracer)
target_include_directories(hollow-glass PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)