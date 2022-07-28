#pragma once

//
//  Object class for QuantitiveBytes tutorial
//

#include "utils/glmutils.h"
#include "raytracer/base.h"

namespace raytracer
{
    class Ray;

    class ObjectBase
    {
    public:
        ObjectBase() = default;
        virtual ~ObjectBase() = default;
        virtual bool testIntersections(const Ray &castRay, Vector3 &intPoint, Vector3 &localNormal, Vector3 &color)=0;

    public:
        Vector3 color;
    };

    using ObjectRef = ref<ObjectBase>;
}