#include "scene.h"

#include <iostream>

#include <raytracer/ray.h>
#include <lights/pointlight.h>

Scene::Scene()
{
    m_camera = new qb::Camera();
    m_camera->setPosition({0, -10, 0});
    m_camera->setLookAt({0, 0, 0});
    m_camera->setUp({0, 0, 1});
    m_camera->setAspect(16.0 / 9.0);
    m_camera->setHorizontalSize(1);
    m_camera->updateGeometry();

    // Create Objects & lights
    {
        using namespace raytracer;

        // Objects
        m_objectList.push_back(createRef<ObjSphere>());

        // Lights
        auto pointLight = createRef<PointLight>();
        pointLight->setPosition({5, -10, -5.0});
        pointLight->setColor({255, 255, 255});

        m_lightList.push_back(pointLight);
    }
}

Scene::~Scene()
{
    delete m_camera;
}

bool Scene::render(qb::Image *outputImage)
{
    if (!outputImage)
        return false;

    // Get the dimensions of the output image
    auto width = outputImage->width();
    auto height = outputImage->height();

    // Loop over each pixel in our image
    raytracer::Ray cameraRay;
    raytracer::Point3 intPoint;
    raytracer::Vector3 localNormal;
    raytracer::Vector3 localColor;

    double xScaleFact = 1.0 / (static_cast<double>(width) / 2.0);
    double yScaleFact = 1.0 / (static_cast<double>(height) / 2.0);
    double minDist = 1e6;
    double maxDist = 0.0;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            double normX = static_cast<double>(x) * xScaleFact - 1.0;
            double normY = static_cast<double>(y) * yScaleFact - 1.0;

            m_camera->generateRay(normX, normY, &cameraRay);

            for (const auto &currentObject : m_objectList)
            {
                bool validIntersection = currentObject->testIntersections(cameraRay, intPoint, localNormal, localColor);

                if (!validIntersection)
                {
                    outputImage->setPixel(x, y, 0.0, 0.0, 0.0);
                    continue;
                }

                double intensity = 0.0;
                raytracer::Color color;
                bool validIllumination = false;
                for (const auto &light : m_lightList)
                {
                    validIllumination = light->computeIllumination(intPoint, localNormal, m_objectList, currentObject, color, intensity);
                }

                double dist = glm::distance(intPoint, cameraRay.origin());

                if (dist > maxDist)
                    maxDist = dist;

                if (dist < minDist)
                    minDist = dist;

                if (!validIllumination)
                {
                    outputImage->setPixel(x, y, 0.0, 0.0, 0.0);
                    continue;
                }

                outputImage->setPixel(x, y, 255.0 * intensity, 0.0, 0.0);
            }
        }
    }

    std::cout << "minDist: " << minDist << std::endl;
    std::cout << "maxDist: " << maxDist << std::endl;

    return true;
}