add_library(raytracer
        raytracer/ray.cpp 
        raytracer/renderer.cpp 
        raytracer/image.cpp 

        utils/timer.cpp 
        utils/orthonormalbasis.cpp 

        cameras/camera.cpp

        hittable/hittablelist.cpp
        hittable/hit_record.cpp
        hittable/aarect.cpp
        hittable/box.cpp
        hittable/bvh.cpp
        hittable/movingsphere.cpp
        hittable/hittable_transformations.cpp
        hittable/constantmedium.cpp
        hittable/flipface.cpp

        materials/lambertian.cpp 
        materials/metal.cpp
        materials/dielectric.cpp 
        materials/diffuselight.cpp
        materials/isotropic.cpp 

        accelerator/aabb.cpp 
         pdf/pdf.cpp
         pdf/cosinepdf.cpp

         textures/solidcolor.cpp
        textures/checkertexture.cpp
         noise/perlin.cpp 
        textures/noisetexture.cpp
        textures/imagetexture.cpp 

       shapes/shape.cpp
        shapes/sphere.cpp 

        image/stb_image.cpp

        geometry/differentialgeometry.cpp

        transformations/transformation.cpp 
        transformations/animatedtransform.cpp
        transformations/geometrictransform.cpp

        primitives/primitive.cpp 

         objects/objectbase.cpp
        objects/objsphere.cpp
      objects/objplane.cpp

        materials/qb/materialbase.cpp materials/qb/simplematerial.cpp

       lights/lightbase.cpp
      lights/pointlight.cpp

        raytracer/intersection.cpp raytracer/intersection.h
         "scene/scene.h" "scene/scene.cpp" "lights/light.h" "samplers/sampler.h" "samplers/sampler.cpp" "integrators/integrator.h" "integrators/integrators.cpp" "samplers/stratifiedsampler.h" "samplers/stratifiedsampler.cpp" "spd/spectrum.h" "spd/spectrum.cpp" "spd/coefficientspectrum.h")


target_include_directories(raytracer
        PRIVATE . ${CMAKE_SOURCE_DIR}/src/3rdparty/stb
        PUBLIC ${CMAKE_SOURCE_DIR}/src/3rdparty/glm
        )