#pragma once

#include "raytracer/base.h"
#include "utils/glmutils.h"

#include <vector>

namespace raytracer
{
    class Ray;
    class ObjectBase;

    class LightBase
    {
    public:
        LightBase() = default;
        virtual ~LightBase() = default;

        virtual bool computeIllumination(const Point3 &intPoint,
                                         const Vector3 &localNormal,
                                         const std::vector<ref<ObjectBase>> &objectList,
                                         const ref<ObjectBase>& currentObject,
                                         Color &color,
                                         double &intensity) = 0;

        Color color() const { return m_color; }
        Point3 position() const { return m_position; }
        double intensity() const { return m_intensity; }

        void setColor(const Color &color) { m_color = color; }
        void setPosition(const Point3 &pos) { m_position = pos; }
        void setIntensity(double inten) { m_intensity = inten; }

    private:
        Color m_color;
        Point3 m_position;
        double m_intensity;
    };

    using LightRef = ref<LightBase>;
}