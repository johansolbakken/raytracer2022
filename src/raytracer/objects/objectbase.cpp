#include "objectbase.h"

#include "raytracer/ray.h"

namespace raytracer
{ /*
     bool testIntersections(const Ray &castRay, Vector3 &intPoint, Vector3 &localNormal, Vector3 &color)
     {
         return false;
     }*/

    bool ObjectBase::setMaterial(const ref<DiffuseMaterialBase> &material)
    {
        m_material = material;
        m_hasMaterial = true;
        return m_hasMaterial;
    }
}