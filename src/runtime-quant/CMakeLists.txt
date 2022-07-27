add_executable(SDLtracer main.cpp app.cpp image.cpp)

target_include_directories(SDLtracer
    PRIVATE . ${CMAKE_SOURCE_DIR}/src/3rdparty/SDL2-msvc/include
)
target_link_directories(SDLtracer
    PRIVATE ${CMAKE_SOURCE_DIR}/src/3rdparty/SDL2-msvc/lib/x64
)
target_link_libraries(SDLtracer
    PRIVATE SDL2 SDL2main
)