add_executable(shiny-metal main.cpp)

target_link_libraries(shiny-metal PRIVATE raytracer)
target_include_directories(shiny-metal PRIVATE ${CMAKE_SOURCE_DIR}/src/raytracer)