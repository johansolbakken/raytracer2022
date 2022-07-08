

add_executable(distant-view main.cpp)

target_link_libraries(distant-view PRIVATE raytracer)
target_include_directories(distant-view PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)