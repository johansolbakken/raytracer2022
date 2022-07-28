#pragma once

#include "lights/lightbase.h"

namespace raytracer
{
    class PointLight : public LightBase
    {
    public:
        PointLight();
        ~PointLight() override = default;

        bool computeIllumination(const Point3 &intPoint,
                                 const Vector3 &localNormal,
                                 const std::vector<ref<ObjectBase>> &objectList,
                                 const ref<ObjectBase>& currentObject,
                                 Vector3 &color,
                                 double &intensity) override;
    };
}