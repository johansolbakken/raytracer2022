

add_executable(Sandbox main.cpp)

target_link_libraries(Sandbox PRIVATE raytracer)
target_include_directories(Sandbox PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)