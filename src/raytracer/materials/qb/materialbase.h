#pragma once

#include "raytracer/base.h"
#include "utils/glmutils.h"
#include "objects/objectbase.h"
#include "lights/lightbase.h"

namespace raytracer
{
    class Ray;

    class DiffuseMaterialBase
    {
    public:
        DiffuseMaterialBase();
        virtual ~DiffuseMaterialBase();

        virtual Color computeColor(const std::vector<ObjectRef> &objectList,
                                   const std::vector<LightRef> &lightList,
                                   const ObjectRef &currentObject,
                                   const Point3 &intPoint,
                                   const Vector3 &localNormal,
                                   const Ray &cameraRay);

        static Color computeDiffuseColor(const std::vector<ObjectRef> &objectList,
                                         const std::vector<LightRef> &lightList,
                                         const ObjectRef &currentObject,
                                         const Point3 &intPoint,
                                         const Vector3 &localNormal,
                                         const Color &localColor);

        Color computeReflectionColor(const std::vector<ObjectRef> &objectList,
                                     const std::vector<LightRef> &lightList,
                                     const ObjectRef &currentObject,
                                     const Point3 &intPoint,
                                     const Vector3 &localNormal,
                                     const Ray &incidentRay);

        bool castRay(const Ray &castRay,
                     const std::vector<ObjectRef> &objectList,
                     const ObjectRef &thisObject,
                     ObjectRef &closestObject,
                     Point3 &intPoint,
                     Vector3 &localNormal,
                     Vector3 &closestColor);

        static int maxReflectionRays() { return m_maxReflectionRays; }
        static int reflectionRayCount() { return m_reflectionRayCount; }
        static void resetReflectionRayCount() { m_reflectionRayCount = 0; }

    private:
        // Counter for number of reflection rays
        inline static int m_maxReflectionRays = 50;
        inline static int m_reflectionRayCount = 0;
    };

    using DiffuseMaterialRef = ref<DiffuseMaterialBase>;
}