#include "scene.h"

#include <iostream>

#include <raytracer/ray.h>

#include <lights/pointlight.h>

#include <objects/objsphere.h>
#include <objects/objplane.h>

Scene::Scene()
{
    m_camera = new qb::Camera();
    m_camera->setPosition({0, -10.0, -2.0});
    m_camera->setLookAt({0, 0, 0});
    m_camera->setUp({0, 0, 1});
    m_camera->setAspect(16.0 / 9.0);
    m_camera->setHorizontalSize(0.25);
    m_camera->updateGeometry();

    // Create Objects & lights
    {
        using namespace raytracer;

        // Objects
        {
            auto sphere1 = createRef<ObjSphere>();
            GeometricTransform trans1;
            trans1.setTransform({-1.5, 0, 0},
                                {0, 0, 0},
                                {0.5, 0.5, 0.75});
            sphere1->setTransform(trans1);
            sphere1->setColor({0.25, 0.5, .8});
            m_objectList.push_back(sphere1);
        }

        {
            auto sphere2 = createRef<ObjSphere>();
            GeometricTransform trans2;
            trans2.setTransform({0, 0, 0},
                                {0, 0, 0},
                                {0.75, 0.5, 0.5});
            sphere2->setTransform(trans2);
            sphere2->setColor({1.0, 0.5, 0.0});
            m_objectList.push_back(sphere2);
        }

        {
            auto sphere3 = createRef<ObjSphere>();
            GeometricTransform trans3;
            trans3.setTransform({1.5, 0.0, 0},
                                {0, 0, 0},
                                {.75, .75, .75});
            sphere3->setTransform(trans3);
            sphere3->setColor({1.0, 0.8, 0});
            m_objectList.push_back(sphere3);
        }

        {
            auto plane = createRef<ObjPlane>();
            GeometricTransform trans4;
            trans4.setTransform({0, 0, 0.75},
                                {0, 0, 0},
                                {4, 4, 1});
            plane->setTransform(trans4);
            plane->setColor({0.5, 0.5, 0.5});
            m_objectList.push_back(plane);
        }

        // Lights
        {
            auto pointLight = createRef<PointLight>();
            pointLight->setPosition({5, -10, -5.0});
            pointLight->setColor({0, 0, 1});
            pointLight->setIntensity(1.0);
            m_lightList.push_back(pointLight);

            auto redLight = createRef<PointLight>();
            redLight->setPosition({-5, -10, -5.0});
            redLight->setColor({1, 0, 0});
            redLight->setIntensity(1.0);
            m_lightList.push_back(redLight);

            auto greenLight = createRef<PointLight>();
            greenLight->setPosition({0, -10, -5.0});
            greenLight->setColor({0, 1, 0});
            greenLight->setIntensity(1.0);
            m_lightList.push_back(greenLight);
        }
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
            double normX = (static_cast<double>(x) * xScaleFact) - 1.0;
            double normY = (static_cast<double>(y) * yScaleFact) - 1.0;

            m_camera->generateRay(normX, normY, &cameraRay);

            // Find the closest object
            raytracer::ObjectRef closesObject;
            raytracer::Point3 closestIntPoint(0.0);
            raytracer::Vector3 closestNormal(0.0);
            raytracer::Vector3 closestObjectColor(0.0);

            double minDist = 1e6;
            bool intersectionFound = false;

            for (const auto &currentObject : m_objectList)
            {
                bool validIntersection = currentObject->testIntersections(cameraRay, intPoint, localNormal, localColor);

                if (!validIntersection)
                    continue;

                intersectionFound = true;

                // Compute the distance between the camera and the point of intersection
                double dist = glm::distance(intPoint, cameraRay.origin()); // TODO: Check if source of error

                if (dist >= minDist)
                    continue;

                minDist = dist;
                closesObject = currentObject;
                closestIntPoint = intPoint;
                closestNormal = localNormal;
                closestObjectColor = localColor;
            }

            if (!intersectionFound)
                continue;

            // Compute the illumination of the object
            double red = 0.0;
            double green = 0.0;
            double blue = 0.0;
            bool illumFound = false;

            double intensity = 0.0;
            raytracer::Color lightColor{0.0};
            bool validIllumination = false;
            for (const auto &currentLight : m_lightList)
            {
                validIllumination = currentLight->computeIllumination(closestIntPoint, closestNormal, m_objectList, closesObject, lightColor, intensity);

                if (!validIllumination)
                    continue;

                illumFound = true;
                red += lightColor.r * intensity;
                green += lightColor.g * intensity;
                blue += lightColor.b * intensity;
            }

            if (!illumFound)
                continue;

            // Add object color
            red *= closestObjectColor.r;
            green *= closestObjectColor.g;
            blue *= closestObjectColor.b;

            outputImage->setPixel(x, y, red, green, blue);
        }
    }

    std::cout << "minDist: " << minDist << std::endl;
    std::cout << "maxDist: " << maxDist << std::endl;

    return true;
}