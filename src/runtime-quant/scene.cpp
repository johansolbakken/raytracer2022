#include "scene.h"

#include <iostream>

#include <raytracer/ray.h>

#include <lights/pointlight.h>

#include <objects/objsphere.h>
#include <objects/objplane.h>
#include <materials/qb/materialbase.h>
#include <materials/qb/simplematerial.h>

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
            auto testMaterial = createRef<SimpleMaterial>();
            testMaterial->setBaseColor({0.25, 0.5, 0.8});
            testMaterial->setShininiess(10.0);
            testMaterial->setReflectivity(0.1);

            auto sphere1 = createRef<ObjSphere>();
            GeometricTransform trans1;
            trans1.setTransform({-1.5, 0, 0},
                                {0, 0, 0},
                                {0.5, 0.5, 0.5});
            sphere1->setTransform(trans1);
            sphere1->setColor({0.25, 0.5, .8});
            sphere1->setMaterial(testMaterial);
            m_objectList.push_back(sphere1);
        }

        {
            auto material2 = createRef<SimpleMaterial>();
            material2->setBaseColor({1.0, 0.5, 0.0});
            material2->setReflectivity(0.75);
            material2->setShininiess(10.0);

            auto sphere2 = createRef<ObjSphere>();
            GeometricTransform trans2;
            trans2.setTransform({0, 0, 0},
                                {0, 0, 0},
                                {0.5, 0.5, 0.5});
            sphere2->setTransform(trans2);
            sphere2->setColor({1.0, 0.5, 0.0});
            sphere2->setMaterial(material2);
            m_objectList.push_back(sphere2);
        }

        {
            auto material3 = createRef<SimpleMaterial>();
            material3->setBaseColor({1.0, 0.8, 0});
            material3->setShininiess(10.0);
            material3->setReflectivity(0.25);

            auto sphere3 = createRef<ObjSphere>();
            GeometricTransform trans3;
            trans3.setTransform({1.5, 0.0, 0},
                                {0, 0, 0},
                                {.5, .5, .5});
            sphere3->setTransform(trans3);
            sphere3->setColor({1.0, 0.8, 0});
            sphere3->setMaterial(material3);
            m_objectList.push_back(sphere3);
        }

        {
            auto floorMaterial = createRef<SimpleMaterial>();
            floorMaterial->setBaseColor({0.5, 0.5, 0.5});
            floorMaterial->setShininiess(0.0);
            floorMaterial->setShininiess(0.5);

            auto plane = createRef<ObjPlane>();
            GeometricTransform trans4;
            trans4.setTransform({0, 0, 0.75},
                                {0, 0, 0},
                                {4, 4, 1});
            plane->setTransform(trans4);
            plane->setColor({0.5, 0.5, 0.5});
            plane->setMaterial(floorMaterial);
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

bool Scene::castRay(raytracer::Ray &castRay,
                    raytracer::ObjectRef &closestObject,
                    raytracer::Point3 &closestIntPoint,
                    raytracer::Vector3 &closestNormal,
                    raytracer::Vector3 &closestColor)
{
    raytracer::Point3 intPoint(0.0);
    raytracer::Vector3 localNormal(0.0);
    raytracer::Vector3 localColor(0.0);

    double minDist = 1e6;
    bool intersectionFound = false;

    for (const auto &currentObject : m_objectList)
    {
        bool validIntersection = currentObject->testIntersections(castRay, intPoint, localNormal, localColor);

        if (!validIntersection)
            continue;

        intersectionFound = true;

        // Compute the distance between the camera and the point of intersection
        double dist = glm::distance(intPoint, castRay.origin()); // TODO: Check if source of error

        if (dist >= minDist)
            continue;

        minDist = dist;
        closestObject = currentObject;
        closestIntPoint = intPoint;
        closestNormal = localNormal;
        closestColor = localColor;
    }

    return intersectionFound;
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

    std::cout << std::endl;
    for (uint32_t y = 0; y < static_cast<uint32_t>(height); y++)
    {
        // Display progress
        std::cout << "\rProcessing line: " << y << " of " << height - 1 << std::flush;
        for (uint32_t x = 0; x < static_cast<uint32_t>(width); x++)
        {

            double normX = (static_cast<double>(x) * xScaleFact) - 1.0;
            double normY = (static_cast<double>(y) * yScaleFact) - 1.0;

            m_camera->generateRay(normX, normY, &cameraRay);

            // Find theß closest object
            raytracer::ObjectRef closestObject;
            raytracer::Point3 closestIntPoint(0.0);
            raytracer::Vector3 closestNormal(0.0);
            raytracer::Vector3 closestObjectColor(0.0);

            bool intersectionFound = castRay(cameraRay, closestObject, closestIntPoint, closestNormal, closestObjectColor);

            if (!intersectionFound)
                continue;

            // Check if object has material
            if (closestObject->hasMaterial())
            {
                // Use material to compute the color
                raytracer::DiffuseMaterialBase::resetReflectionRayCount();
                auto color = closestObject->material()->computeColor(m_objectList, m_lightList, closestObject, closestIntPoint, closestNormal, cameraRay);
                outputImage->setPixel(x, y, color.r, color.g, color.b);
            }
            else
            {
                auto color = raytracer::DiffuseMaterialBase::computeDiffuseColor(m_objectList, m_lightList, closestObject, closestIntPoint, closestNormal, closestObjectColor);
                outputImage->setPixel(x, y, color.r, color.g, color.b);
            }
        }
    }

    std::cout << std::endl
              << "Done!" << std::endl;

    return true;
}