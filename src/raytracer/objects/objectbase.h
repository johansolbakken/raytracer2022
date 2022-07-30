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
    class DiffuseMaterialBase;

    class ObjectBase
    {
    public:
        ObjectBase() = default;
        virtual ~ObjectBase() = default;
        virtual bool testIntersections(const Ray &castRay, Vector3 &intPoint, Vector3 &localNormal, Color &color) = 0;

        void setColor(const Color &color) { m_color = color; }
        void setTransform(const GeometricTransform &trans) { m_transform = trans; }
        bool setMaterial(const ref<DiffuseMaterialBase> &material);
        bool hasMaterial() const { return m_hasMaterial; }

        GeometricTransform transform() const { return m_transform; }
        ref<DiffuseMaterialBase> material() const { return m_material; }
        Color color() const { return m_color; }

    public:
        Color m_color;
        GeometricTransform m_transform;
        ref<DiffuseMaterialBase> m_material;
        bool m_hasMaterial;
    };

    using ObjectRef = ref<ObjectBase>;
}