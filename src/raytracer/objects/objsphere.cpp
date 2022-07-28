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
        // Calculate b and c
        double b = 2.0 * glm::dot(castRay.origin(), castRay.direction());
        double c = glm::dot(castRay.origin(), castRay.origin()) - 1.0;

        // Test whether we have an intersection
        double intTest = (b * b) - 4.0 * c;
        if (intTest > 0.0)
        {
            double numSQRT = std::sqrt(intTest);
            double t1 = (-b + numSQRT) / 2.0;
            double t2 = (-b - numSQRT) / 2.0;

            if (t1 < 0.0 || t2 < 0.0)
                return false;

            if (t1 < t2)
            {
                intPoint = castRay.at(t1);
            } else {
                intPoint = castRay.at(t2);
            }
            
            localNormal = glm::normalize(intPoint);

            return true;
        }

        return false;
    }
}

// TODO: Neste episode: https://www.youtube.com/watch?v=-Apu2BNp3t8