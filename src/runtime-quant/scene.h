#pragma once

#include <memory>
#include <vector>
#include <SDL.h>
#include "image.h"
#include "camera.h"

#include <objects/objectbase.h>
#include <lights/lightbase.h>

class Scene
{
public:
    Scene();
    ~Scene();

    bool render(qb::Image *outputImage);

private:
    bool castRay(raytracer::Ray &castRay,
                 raytracer::ObjectRef &closestObject,
                 raytracer::Point3 &closestIntPoint,
                 raytracer::Vector3 &closestNormal,
                 raytracer::Vector3 &closestColor);

private:
    qb::Camera *m_camera;

    // List of objects in the scene
    std::vector<raytracer::ObjectRef> m_objectList;
    std::vector<raytracer::LightRef> m_lightList;
};