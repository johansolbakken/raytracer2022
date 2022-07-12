

add_executable(cornell-smoke main.cpp)

target_link_libraries(cornell-smoke PRIVATE raytracer)
target_include_directories(cornell-smoke PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)