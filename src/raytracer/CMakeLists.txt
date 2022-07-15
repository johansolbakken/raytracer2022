add_library(raytracer
        raytracer.h
        raytracer/ray.cpp raytracer/ray.h
        raytracer/base.h
        raytracer/renderer.cpp raytracer/renderer.h
        raytracer/image.cpp raytracer/image.h

        utils/glmutils.h
        utils/mathutils.h
        utils/timer.cpp utils/timer.h
        utils/orthonormalbasis.cpp utils/orthonormalbasis.h

        cameras/camera.cpp cameras/camera.h

        hittable/hittable.h
        hittable/hittablelist.cpp hittable/hittablelist.h
        hittable/hit_record.h hittable/hit_record.cpp
        hittable/aarect.h hittable/aarect.cpp
        hittable/box.cpp hittable/box.h
        hittable/bvh.cpp hittable/bvh.h
        hittable/movingsphere.cpp hittable/movingsphere.h
        hittable/hittable_transformations.h hittable/hittable_transformations.cpp
        hittable/constantmedium.cpp hittable/constantmedium.h
        hittable/flipface.h hittable/flipface.cpp

        materials/material.h
        materials/lambertian.cpp materials/lambertian.h
        materials/metal.cpp materials/metal.h
        materials/dielectric.cpp materials/dielectric.h
        materials/diffuselight.cpp materials/diffuselight.h
        materials/isotropic.cpp materials/isotropic.h

        accelerator/aabb.cpp accelerator/aabb.h
        pdf/pdf.h pdf/pdf.cpp
        pdf/cosinepdf.h pdf/cosinepdf.cpp

        textures/texture.h textures/solidcolor.cpp
        textures/solidcolor.h textures/checkertexture.cpp
        textures/checkertexture.h noise/perlin.cpp noise/perlin.h
        textures/noisetexture.cpp textures/noisetexture.h
        textures/imagetexture.cpp textures/imagetexture.h

        shapes/shape.h shapes/shape.cpp
        shapes/sphere.cpp shapes/sphere.h

        image/stb_image.cpp

        geometry/differentialgeometry.cpp geometry/differentialgeometry.h

        transformations/transformation.cpp transformations/transformation.h
        transformations/animatedtransform.cpp transformations/animatedtransform.h

        primitives/primitive.cpp primitives/primitive.h

        raytracer/intersection.cpp raytracer/intersection.h
         "scene/scene.h" "scene/scene.cpp" "lights/light.h")


target_include_directories(raytracer
        PRIVATE . ${CMAKE_SOURCE_DIR}/src/3rdparty/stb
        PUBLIC ${CMAKE_SOURCE_DIR}/src/3rdparty/glm
        )