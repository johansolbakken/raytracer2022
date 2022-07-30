#pragma once

#include "materialbase.h"

namespace raytracer
{
    class SimpleMaterial : public DiffuseMaterialBase
    {
    public:
        SimpleMaterial() = default;
        ~SimpleMaterial() override = default;

        Color computeColor(const std::vector<ObjectRef> &objectList,
                           const std::vector<LightRef> &lightList,
                           const ObjectRef &currentObject,
                           const Point3 &intPoint,
                           const Vector3 &localNormal,
                           const Ray &cameraRay) override;

        Color computeSpecular(const std::vector<ObjectRef> &objectList,
                              const std::vector<LightRef> &lightList,
                              const Point3 &intPoint,
                              const Vector3 &localNormal,
                              const Ray &cameraRay);

        Color baseColor() const { return m_baseColor; }
        double reflectivity() const { return m_reflectivity; }
        double shininiess() const { return m_shininess; }

        void setBaseColor(const Color &color) { m_baseColor = color; }
        void setReflectivity(double reflectivity) { m_reflectivity = reflectivity; }
        void setShininiess(double shine) { m_shininess = shine; }

    private:
        Color m_baseColor = {1, 0, 1};
        double m_reflectivity = 0.0;
        double m_shininess = 0.0;
    };
}