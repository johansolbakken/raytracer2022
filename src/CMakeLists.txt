# 3rd party
add_subdirectory(3rdparty/glm)
add_subdirectory(3rdparty/stb)

# raytracer
add_subdirectory(raytracer)

# working area
add_subdirectory(examples/sandbox)

# examples
set(BUILD_EXAMPLES YES)
if (BUILD_EXAMPLES)
    add_subdirectory(examples/shiny-metal)
    add_subdirectory(examples/hollow-glass)
    add_subdirectory(examples/wide-angle-camera)
    add_subdirectory(examples/distant-view)
    add_subdirectory(examples/focus-scene)
    add_subdirectory(examples/moving-spheres)
    add_subdirectory(examples/two-checkered-spheres)
    add_subdirectory(examples/noise)
    add_subdirectory(examples/earth-image)
    add_subdirectory(examples/marble-light)
    add_subdirectory(examples/empry-cornell)
endif (BUILD_EXAMPLES)