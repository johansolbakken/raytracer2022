#include "objplane.h"

#include "raytracer/ray.h"
#include "utils/mathutils.h"

namespace raytracer
{
    bool ObjPlane::testIntersections(const Ray &castRay, Vector3 &intPoint, Vector3 &localNormal, Color &color)
    {
        auto backRay = transform().apply(castRay, TransformFlag::Backward);

        // If transformed z is close to 0.0, we are most likely parallell
        if (equalsDouble(backRay.direction().z, 0.0))
            return false;

        double t = backRay.origin().z / (-backRay.direction().z);

        // T < 0.0 => behind camera
        if (t <= 0.0)
            return false;

        // Calculate intersections
        Point3 intersectionPoint = backRay.at(t);
        double u = intersectionPoint.x;
        double v = intersectionPoint.y;

        // We only have intersection if u and v are less than 1.
        if ((std::abs(u) >= 1.0) || (std::abs(v) >= 1.0))
            return false;

        // Intersection point in world coordinates
        auto poi = intersectionPoint;
        intPoint = transform().apply(poi, TransformFlag::Forward);

        // Compute normal
        Point3 localOrigin = {0, 0, 0};
        auto globalOrigin = transform().apply(localOrigin, TransformFlag::Forward);
        Vector3 normalVector = {0, 0, -1};
        localNormal = transform().apply(normalVector, TransformFlag::Forward) - globalOrigin;
        localNormal = glm::normalize(localNormal);

        // Return the base color
        color = this->color();

        return true;
    }
    
}