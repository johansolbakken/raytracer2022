#include "materials/qb/materialbase.h"

#include "raytracer/ray.h"

namespace raytracer
{
    DiffuseMaterialBase::DiffuseMaterialBase()
    {
    }

    DiffuseMaterialBase::~DiffuseMaterialBase()
    {
    }

    Color DiffuseMaterialBase::computeColor(const std::vector<ObjectRef> &objectList,
                                            const std::vector<LightRef> &lightList,
                                            const ObjectRef &closestObject,
                                            const Point3 &closestIntPoint,
                                            const Vector3 &closestNormal,
                                            const Ray &cameraRay)
    {
        Color color(0.0);

        return color;
    }

    Color DiffuseMaterialBase::computeDiffuseColor(const std::vector<ObjectRef> &objectList,
                                                   const std::vector<LightRef> &lightList,
                                                   const ObjectRef &currentObject,
                                                   const Point3 &intPoint,
                                                   const Vector3 &localNormal,
                                                   const Color &baseColor)
    {
        double intensity;
        Color color(0.0);

        double red = 0.0;
        double green = 0.0;
        double blue = 0.0;

        bool illumFound = false;

        for (const auto &currentLight : lightList)
        {
            bool validIllum = currentLight->computeIllumination(intPoint,
                                                                localNormal,
                                                                objectList,
                                                                currentObject,
                                                                color,
                                                                intensity);

            if (!validIllum)
                continue;

            illumFound = true;

            red += color.r * intensity;
            green += color.g * intensity;
            blue += color.b * intensity;
        }

        if (!illumFound)
            return {0, 0, 0};

        Color diffuseColor(0.0);
        diffuseColor.r = red * baseColor.r;
        diffuseColor.g = green * baseColor.g;
        diffuseColor.b = blue * baseColor.b;

        return diffuseColor;
    }

    Color DiffuseMaterialBase::computeReflectionColor(const std::vector<ObjectRef> &objectList,
                                                      const std::vector<LightRef> &lightList,
                                                      const ObjectRef &currentObject,
                                                      const Point3 &intPoint,
                                                      const Vector3 &localNormal,
                                                      const Ray &incidentRay)
    {
        // Compute reflection vector
        auto d = incidentRay.direction();
        auto reflectionVector = d - (2 * glm::dot(d, localNormal) * localNormal);

        // Construct the reflection ray
        Ray reflectionRay;
        reflectionRay.setOrigin(intPoint);
        reflectionRay.setDirection(intPoint + reflectionVector);

        // Cast this ray into the scene and find the closest object that is intersects with
        ObjectRef closestObject;
        Point3 closestIntPoint;
        Vector3 closestNormal;
        Color closestColor;

        bool intersectionFound = castRay(reflectionRay,
                                         objectList,
                                         currentObject,
                                         closestObject,
                                         closestIntPoint,
                                         closestNormal,
                                         closestColor);

        // If there is not intersection, or maximum recursion depth has been exceeded, return blackß
        if ((!intersectionFound) || (m_reflectionRayCount >= m_maxReflectionRays))
        {
            return {0, 0, 0};
        }

        // Recursively find reflection
        Color reflectionColor(0.0);
        {
            m_reflectionRayCount++;
            if (closestObject->hasMaterial())
            {
                reflectionColor = closestObject->material()->computeColor(objectList,
                                                                          lightList,
                                                                          closestObject,
                                                                          closestIntPoint,
                                                                          closestNormal,
                                                                          reflectionRay);
            }
            else
            {
                reflectionColor = DiffuseMaterialBase::computeDiffuseColor(objectList,
                                                                           lightList,
                                                                           closestObject,
                                                                           closestIntPoint,
                                                                           closestNormal,
                                                                           closestObject->color());
            }
        }

        return reflectionColor;
    }

    bool DiffuseMaterialBase::castRay(const Ray &castRay,
                                      const std::vector<ObjectRef> &objectList,
                                      const ObjectRef &thisObject,
                                      ObjectRef &closestObject,
                                      Point3 &closestIntPoint,
                                      Vector3 &closestNormal,
                                      Vector3 &closestColor)
    {
        Point3 intPoint;
        Vector3 localNormal;
        Color localColor;
        double minDist = 1e6;
        bool intersectionFound = false;

        for (const auto &currentObject : objectList)
        {
            // Prevent self reflection
            if (currentObject == thisObject)
                continue;

            // Calculate reflection
            bool validIntersection = currentObject->testIntersections(castRay,
                                                                      intPoint,
                                                                      localNormal,
                                                                      localColor);
            if (!validIntersection)
                continue;

            // We have an intersection
            intersectionFound = true;

            // Distance between intersection point and the cast rays origin
            double dist = glm::distance(intPoint, castRay.origin());

            // If it is not the closest object, go to the next object
            if (dist >= minDist)
                continue;

            // It is the closest object.
            minDist = dist;
            closestObject = currentObject;
            closestIntPoint = intPoint;
            closestNormal = localNormal;
            closestColor = localColor;
        }

        return intersectionFound;
    }
}