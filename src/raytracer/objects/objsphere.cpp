#include "objsphere.h"

#include "raytracer/ray.h"

namespace raytracer
{
    ObjSphere::ObjSphere()
    {
    }

    bool ObjSphere::testIntersections(const Ray &castRay,
                                      Vector3 &intPoint,
                                      Vector3 &localNormal,
                                      Vector3 &color)
    {
        // Transform the ray into local sphere coordinates
        auto transformedRay = transform().apply(castRay, TransformFlag::Backward);

        // Calculate b and c
        double b = 2.0 * glm::dot(transformedRay.origin(), transformedRay.direction());
        double c = glm::dot(transformedRay.origin(), transformedRay.origin()) - 1.0;

        // Test whether we have an intersection
        double intTest = (b * b) - 4.0 * c;

        Point3 pointOfIntersection;
        if (intTest > 0.0)
        {
            double numSQRT = std::sqrt(intTest);
            double t1 = (-b + numSQRT) / 2.0;
            double t2 = (-b - numSQRT) / 2.0;

            if (t1 < 0.0 || t2 < 0.0)
                return false;

            if (t1 < t2)
            {
                pointOfIntersection = transformedRay.at(t1);
            }
            else
            {
                pointOfIntersection = transformedRay.at(t2);
            }

            // Transform intersection back into world coordinates
            intPoint = transform().apply(pointOfIntersection, TransformFlag::Forward);

            // Compute the local normal
            Point3 objOrigin = transform().apply({0, 0, 0}, TransformFlag::Forward);
            localNormal = glm::normalize(pointOfIntersection - objOrigin);

            // Return the base color
            color = this->color();

            return true;
        }

        return false;
    }
}
