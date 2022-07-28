#pragma once

#include "objects/objectbase.h"

namespace raytracer
{
    class ObjSphere : public ObjectBase
    {
    public:
        ObjSphere();
        ~ObjSphere() override = default;

        bool testIntersections(const Ray &castRay,
                               Vector3 &intPoint,
                               Vector3 &localNormal,
                               Vector3 &color) override;
    };
}