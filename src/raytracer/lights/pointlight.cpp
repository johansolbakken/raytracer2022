#include "pointlight.h"

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
                                         const std::vector<ref<ObjectBase>> &objectList,
                                         const ref<ObjectBase> &currentObject,
                                         Color &color,
                                         double &intensity)

    {
        auto lightDir = glm::normalize(position() - intPoint);
        auto startPoint = intPoint;
        auto angle = std::acos(glm::dot(localNormal, lightDir));

        constexpr auto piBy2 = math::pi / 2.0;

        if (angle > piBy2)
        {
            // No color
            color = this->color();
            intensity = 0.0;
            return false;
        }

        color = this->color();
        intensity = this->intensity() * (1.0 - (angle / piBy2));
        return true;
    }
}