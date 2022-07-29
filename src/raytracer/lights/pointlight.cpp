#include "pointlight.h"

#include <raytracer/ray.h>

#include <objects/objectbase.h>

namespace raytracer
{
    PointLight::PointLight()
    {
        setColor({1, 1, 1});
        setIntensity(1.0);
        setPosition({0, 0, 0});
    }

    bool PointLight::computeIllumination(const Point3 &intPoint,
                                         const Vector3 &localNormal,
                                         const std::vector<ObjectRef> &objectList,
                                         const ref<ObjectBase> &currentObject,
                                         Color &color,
                                         double &intensity)

    {
        // Default values
        color = {0, 0, 0};
        intensity = 0;

        // Computing light direction and startPoint
        auto lightDirection = glm::normalize(position() - intPoint);
        auto startPoint = intPoint;

        // Calculate shadow - cast shadow from point of intersection to light
        raytracer::Ray lightRay;
        lightRay.setOrigin(startPoint);
        lightRay.setDirection(lightDirection);

        Point3 poi;
        Vector3 poiNormal;
        Vector3 poiColor;
        bool lightRayHit = false;

        for (const auto &other : objectList)
        {
            if (currentObject == other)
                continue;

            lightRayHit = other->testIntersections(lightRay, poi, poiNormal, poiColor);

            if (lightRayHit)
                break;
        }

        bool wasShadowRay = lightRayHit;
        if (wasShadowRay)
            return false;

        constexpr auto piBy2 = math::pi / 2.0;
        auto angle = std::acos(glm::dot(localNormal, lightDirection));
        bool lightPointsAtObject = angle < piBy2;
        if (!lightPointsAtObject)
            return false;

        // Illuminate!
        color = this->color();
        intensity = this->intensity() * (1.0 - (angle / piBy2));
        return true;
    }
}