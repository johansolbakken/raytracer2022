

add_executable(earth-image main.cpp)

target_link_libraries(earth-image PRIVATE raytracer)
target_include_directories(earth-image PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)