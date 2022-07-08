

add_executable(wide-angle-camera main.cpp)

target_link_libraries(wide-angle-camera PRIVATE raytracer)
target_include_directories(wide-angle-camera PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)