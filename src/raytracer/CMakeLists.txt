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
        materials/lambertian.cpp materials/lambertian.h)

target_include_directories(raytracer
        PRIVATE .
        PUBLIC ${CMAKE_SOURCE_DIR}/src/3rdparty/glm
        )