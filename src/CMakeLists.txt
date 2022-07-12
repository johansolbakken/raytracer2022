# 3rd party
add_subdirectory(3rdparty/glm)

# raytracer
add_subdirectory(raytracer)
add_subdirectory(editor)

# working area
add_subdirectory(examples/sandbox)

# examples
option(BUILD_EXAMPLES "Build examples" YES)
if (YES)
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
    add_subdirectory(examples/cornell-smoke)
    add_subdirectory(examples/all-features-1)
endif ()
