add_library(raytracer
        raytracer.h
        raytracer/ray.cpp raytracer/ray.h
        raytracer/base.h
        raytracer/renderer.cpp raytracer/renderer.h
        raytracer/image.cpp raytracer/image.h

        utils/glmutils.h
        utils/mathutils.h

        cameras/camera.cpp cameras/camera.h

        hittable/hittable.h
        hittable/sphere.cpp hittable/sphere.h
        hittable/hittablelist.cpp hittable/hittablelist.h
        hittable/hit_record.h hittable/hit_record.cpp

        materials/material.h
        materials/lambertian.cpp materials/lambertian.h materials/metal.cpp materials/metal.h materials/dielectric.cpp materials/dielectric.h accelerator/aabb.cpp accelerator/aabb.h hittable/bvh.cpp hittable/bvh.h hittable/movingsphere.cpp hittable/movingsphere.h textures/texture.h textures/solidcolor.cpp textures/solidcolor.h textures/checkertexture.cpp textures/checkertexture.h noise/perlin.cpp noise/perlin.h textures/noisetexture.cpp textures/noisetexture.h)

target_link_libraries(raytracer
        PRIVATE stb_image
        )

target_include_directories(raytracer
        PRIVATE . ${CMAKE_SOURCE_DIR}/src/3rdparty/stb
        PUBLIC ${CMAKE_SOURCE_DIR}/src/3rdparty/glm
        )