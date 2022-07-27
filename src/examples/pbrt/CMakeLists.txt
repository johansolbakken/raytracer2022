

add_executable(pbrt pbrt.cpp)

target_link_libraries(pbrt PRIVATE raytracer)
target_include_directories(pbrt PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)