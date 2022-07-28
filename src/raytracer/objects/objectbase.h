#pragma once

//
//  Object class for QuantitiveBytes tutorial
//

#include "utils/glmutils.h"
#include "raytracer/base.h"
#include "transformations/geometrictransform.h"

namespace raytracer
{
    class Ray;

    class ObjectBase
    {
    public:
        ObjectBase() = default;
        virtual ~ObjectBase() = default;
        virtual bool testIntersections(const Ray &castRay, Vector3 &intPoint, Vector3 &localNormal, Color &color) = 0;

        void setTransform(const GeometricTransform &trans) { m_transform = trans; }

        GeometricTransform transform() const { return m_transform; }

        void setColor(const Color &color) { m_color = color; }
        Color color() const { return m_color; }

    public:
        Color m_color;
        GeometricTransform m_transform;
    };

    using ObjectRef = ref<ObjectBase>;
}