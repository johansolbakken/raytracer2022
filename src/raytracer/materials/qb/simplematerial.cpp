#include "simplematerial.h"

#include "raytracer/ray.h"

namespace raytracer
{
    Color SimpleMaterial::computeColor(const std::vector<ObjectRef> &objectList,
                                       const std::vector<LightRef> &lightList,
                                       const ObjectRef &currentObject,
                                       const Point3 &intPoint,
                                       const Vector3 &localNormal,
                                       const Ray &cameraRay)
    {
        // Compute diffuse component
        Color diffuseColor = DiffuseMaterialBase::computeDiffuseColor(objectList,
                                                                      lightList,
                                                                      currentObject,
                                                                      intPoint,
                                                                      localNormal,
                                                                      m_baseColor);

        // Compute the reflection component
        Color reflectionColor(0.0);
        if (m_reflectivity > 0.0)
        {
            reflectionColor = computeReflectionColor(objectList,
                                                     lightList,
                                                     currentObject,
                                                     intPoint,
                                                     localNormal,
                                                     cameraRay);
        }

        // Combine diffuse and reflectivity color
        Color materialColor = (m_reflectivity * reflectionColor) + (1 - m_reflectivity) * diffuseColor;

        // Compute specular color
        Color specularColor(0.0);
        if (m_shininess > 0.0)
        {
            specularColor = computeSpecular(objectList,
                                            lightList,
                                            intPoint,
                                            localNormal,
                                            cameraRay);
        }

        // Combine the specular color with diffuse and reflectivity color mix.
        materialColor = materialColor + specularColor;
        return materialColor;
    }

    Color SimpleMaterial::computeSpecular(const std::vector<ObjectRef> &objectList,
                                          const std::vector<LightRef> &lightList,
                                          const Point3 &intPoint,
                                          const Vector3 &localNormal,
                                          const Ray &cameraRay)
    {
        double red = 0.0;
        double green = 0.0;
        double blue = 0.0;

        for (const auto &currentLight : lightList)
        {
            // Construct light ray
            auto lightDir = glm::normalize(currentLight->position() - intPoint);
            auto startPoint = intPoint + (lightDir * 0.001);

            Ray lightRay;
            lightRay.setOrigin(startPoint);
            lightRay.setDirection(startPoint + lightDir);

            // Check if light ray intersects with any objects
            Point3 poi;
            Vector3 poiNormal;
            Color poiColor;
            bool validInt = false;
            for (const auto &sceneObject : objectList)
            {
                validInt = sceneObject->testIntersections(lightRay, poi, poiNormal, poiColor);
                if (validInt)
                    break;
            }

            // If there was an intersecting object, go to next light
            double intensity = 0.0;
            if (!validInt)
            {

                // Compute the reflection vector
                Vector3 d = lightRay.direction();
                auto r = glm::normalize(d - (2 * glm::dot(d, localNormal) * localNormal));

                // Compute the dot product
                auto v = cameraRay.direction();
                double dotProduct = glm::dot(r, v);
                if (dotProduct > 0.0)
                {
                    // Calculate the intensity
                    intensity = m_reflectivity * std::pow(dotProduct, m_shininess);
                }
            }

            red += currentLight->color().r * intensity;
            green += currentLight->color().g * intensity;
            blue += currentLight->color().b * intensity;
        }

        Color specularColor = {red, green, blue};
        return specularColor;
    }
}