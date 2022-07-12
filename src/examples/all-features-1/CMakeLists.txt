

add_executable(all-features-1 main.cpp)

target_link_libraries(all-features-1 PRIVATE raytracer)
target_include_directories(all-features-1 PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)