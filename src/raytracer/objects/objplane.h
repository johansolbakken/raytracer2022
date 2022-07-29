#pragma once

#include "objectbase.h"

namespace raytracer
{
    class ObjPlane : public ObjectBase
    {
    public:
        ObjPlane() = default;
        ~ObjPlane() override = default;

        bool testIntersections(const Ray &castRay, Vector3 &intPoint, Vector3 &localNormal, Color &color) override;

    private:
    };
}