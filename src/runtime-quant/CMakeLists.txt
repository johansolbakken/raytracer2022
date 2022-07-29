add_executable(SDLtracer main.cpp app.h app.cpp image.h image.cpp scene.h scene.cpp camera.h camera.cpp) 

target_include_directories(SDLtracer
    PUBLIC ${CMAKE_SOURCE_DIR}/src/raytracer ${CMAKE_SOURCE_DIR}/src/3rdparty/glm
)
target_link_libraries(SDLtracer
    PUBLIC raytracer
)

if (WIN32)
target_include_directories(SDLtracer
    PRIVATE . ${CMAKE_SOURCE_DIR}/src/3rdparty/SDL2-msvc/include
)
target_link_directories(SDLtracer
    PRIVATE ${CMAKE_SOURCE_DIR}/src/3rdparty/SDL2-msvc/lib/x64
)
target_link_libraries(SDLtracer
    PRIVATE SDL2 SDL2main
)
endif()

if(APPLE)
    find_package(SDL2 REQUIRED)
    
    target_include_directories(SDLtracer
    PRIVATE . ${SDL2_INCLUDE_DIRS})

    target_link_libraries(SDLtracer
    PRIVATE ${SDL2_LIBRARIES}
)
endif()