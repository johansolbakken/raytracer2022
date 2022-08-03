
add_executable(ray_test raytracer/ray_test.cpp)
target_link_libraries(ray_test PRIVATE raytracer gtest gtest_main)
target_include_directories(ray_test PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)
add_test(NAME ray_test COMMAND ray_test)