#include "scene.h"

Scene::Scene()
{

}

bool Scene::render(qb::Image* outputImage)
{
    if (!outputImage) return false;

    auto width = outputImage->width();
    auto height = outputImage->height();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double red = (static_cast<double>(x)/static_cast<double>(width)) * 255.0;
            double green = (static_cast<double>(y)/static_cast<double>(height)) * 255.0;
            outputImage->setPixel(x, y, red, green, 0.0);
        }
    }

    return true;
}