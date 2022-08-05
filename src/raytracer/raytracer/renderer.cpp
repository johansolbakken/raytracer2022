#include "renderer.h"

#include "raytracer/base.h"
#include "raytracer/image.h"
#include "raytracer/ray.h"

#include "hittable/hittable.h"

#include "cameras/camera.h"

#include "utils/mathutils.h"

#include "materials/material.h"

#include <iostream>

#include <pdf/cosinepdf.h>

#define cherno 1

namespace utils {
static uint32_t convertToRGBA(const raytracer::Vector4& color) {
    uint8_t r = (uint8_t)(color.r * 255.0);
    uint8_t g = (uint8_t)(color.g * 255.0);
    uint8_t b = (uint8_t)(color.b * 255.0);
    uint8_t a = (uint8_t)(color.a * 255.0);

    uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
    return result;
}
}

namespace raytracer
{
void Renderer::render(const ref<Hittable>& world, const ref<Camera>& camera)
{
    m_shouldAbort = false;
    m_camera = camera;
    m_world = world;

    resetScanlines();

    if (!m_finalImage || !m_imageData) return;

    if (m_multithread) renderMultithread();
    else renderSinglethread();
}

void Renderer::renderSinglethread()
{
    for (int y = m_finalImage->height() - 1; y >= 0; y--)
    {
        for (int x = 0; x < int(m_finalImage->width()); x++)
        {
            {
                std::lock_guard guard(m_abort_mutex);
                if (m_shouldAbort) {
                    return;
                }

            }


#if cherno
            // Normalize coordinate
            glm::vec2 coord = {
                (double)x / (double)m_finalImage->width(),
                (double)y / (double)m_finalImage->height()
            };
            coord = coord * 2.0f - 1.0f;
#else   //cherno
            auto u = double(x) / (m_finalImage->width()-1);
            auto v = double(y) / (m_finalImage->height()-1);
            glm::vec2 coord = { u, v };
#endif  // cherno
            auto color = perPixel(coord);
            int pos = x + (m_finalImage->height() - y - 1) * m_finalImage->width();
            color = glm::clamp(color, Vector4(0.0), Vector4(1.0));
            m_imageData[pos] = utils::convertToRGBA(color);
            std::lock_guard guard(m_finalImage->mutex());
            m_finalImage->data()[pos] = m_imageData[pos];
        }
        incrementScanlines();
        if (m_callback) m_callback(scanlines());
    }

    m_finalImage->setData(m_imageData);
}

void Renderer::renderMultithread()
{
    int numThreads = 2;
    int sections = std::thread::hardware_concurrency() / numThreads;

    std::vector<Color> buffer(m_finalImage->width() * m_finalImage->height());
    for (int i = 0; i < int(m_finalImage->width() * m_finalImage->height()); i++) {
        buffer[i] = Color{0};
    }

    auto perPixelDouble = [&](glm::vec2 coord){
        Color pixel_color(0.0, 0.0, 0.0);
        for (int s = 0; s < m_Specification.samplesPerPixel; ++s)
        {
            Ray r = m_camera->getRay(coord.x, coord.y);
            pixel_color += rayColor(r, m_world, m_Specification.recursionDepth);
        }

        auto r = pixel_color.x;
        auto g = pixel_color.y;
        auto b = pixel_color.z;

        return Color{r, g, b};
    };

    auto thread = [&](int y0, int y1, std::mutex *mutex){
        for (int y = y0; y < y1; y++)
        {
            for (int x = 0; x < int(m_finalImage->width()); x++)
            {
                {
                    std::lock_guard guard(m_abort_mutex);
                    if (m_shouldAbort) {
                        return;
                    }
                }

                auto u = double(x) / (m_finalImage->width()-1);
                auto v = double(y) / (m_finalImage->height()-1);
                glm::vec2 coord = { u, v };

                auto color = perPixelDouble(coord);
                std::unique_lock guard(*mutex);
                buffer[x + y * m_finalImage->width()] += color;
            }
        }
    };

    auto section = [&](int y0, int y1){
        std::vector<std::future<void>> pool;

        std::mutex m_bufferMutex;

        for (int i = 0; i < numThreads; i++) {
            pool.push_back(std::async(std::launch::async, thread, y0, y1, &m_bufferMutex));
        }
    };

    std::vector<std::future<void>> pool;

    int delta = m_finalImage->height() / sections;
    int yOld = 0;
    int y = delta;
    for (int i = 0; i <  sections; i++) {
        pool.push_back(std::async(std::launch::async, section, yOld, y));
        yOld = y;
        y+= delta;
        if (y >= int(m_finalImage->height())) y = m_finalImage->height() ;
    }

    for (auto& t : pool) {
        t.wait();
    }

    for (int i = 0; i < int(m_finalImage->width() * m_finalImage->height()); i++) {
        auto color = buffer[i];
        m_imageData[i] = gammaCorrectToUint(color.r, color.g, color.b);
    }

    m_finalImage->setData(m_imageData);
}

Color Renderer::rayColor(const Ray& ray, const ref<Hittable>& world, int depth)
{
    hit_record rec{};

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return { 0, 0, 0 };

    // If the ray hits nothing, return the background color.
    if (!world->hit(ray, 0.001, math::infinity, rec))
        return m_Specification.backgroundColor;

    Ray scattered;
    Color albedo;
    double pdf_val;
    Color emitted = rec.mat_ptr->emitted(ray, rec, rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(ray, rec, albedo, scattered, pdf_val))
        return emitted;

    CosinePdf p(rec.normal);
    scattered = Ray(rec.p, p.generate(), ray.time());
    pdf_val = p.value(scattered.direction());

    return emitted + albedo * rec.mat_ptr->scatteringPdf(ray, rec, scattered)
            * rayColor(scattered, world, depth - 1) / pdf_val;
}

uint32_t Renderer::gammaCorrectToUint(double r, double g, double b)
{
    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / m_Specification.samplesPerPixel;
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    auto ri = static_cast<uint32_t>(256 * clamp(r, 0.0, 0.999));
    auto gi = static_cast<uint32_t>(256 * clamp(g, 0.0, 0.999));
    auto bi = static_cast<uint32_t>(256 * clamp(b, 0.0, 0.999));

    return 0xff000000 | (bi << 16) | (gi << 8) | ri;
}

Renderer::Renderer(const RendererSpecification& spec)
{
    init(spec);
}

Vector4 Renderer::perPixel(glm::vec2 coord)
{
#if cherno
    auto r = (uint8_t)(coord.x*255.0);
    auto g = (uint8_t(coord.y * 255.0));

    Point3 rayOrigin(0,0,1.0);
    Vector3 rayDirection(coord.x, coord.y, -1.0);
    rayDirection = glm::normalize(rayDirection);
    double radius = 0.5;

    double a = glm::dot(rayDirection, rayDirection);
    double b = 2.0 * glm::dot(rayOrigin, rayDirection);
    double c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

    double descriminant = b * b - 4.0 * a * c;

    if (descriminant < 0.0)
        return Color4(0,0,0,1);

    Color sphereColor(1,0,1);

    double t0 = -b + std::sqrt(descriminant) / (2.0 * a);
    double t1 = -b - std::sqrt(descriminant) / (2.0 * a);

    Point3 hitPosition0 = rayOrigin + rayDirection * t0;
    Point3 hitPosition1 = rayOrigin + rayDirection * t1;

    Vector3 normal1 = glm::normalize(hitPosition1); /* - sphere origin */

    Vector3 lightDirection = glm::normalize(Vector3(-1, -1, -1));
    float d = std::max(0.0, glm::dot(normal1, -lightDirection));

    sphereColor *= d;

    return Color4(sphereColor, 1.0);
#else
    Color pixel_color(0, 0, 0);
    for (int s = 0; s < m_Specification.samplesPerPixel; ++s)
    {
        Ray r = m_camera->getRay(coord.x, coord.y);
        pixel_color += rayColor(r, m_world, m_Specification.recursionDepth);
    }

    auto r = pixel_color.x;
    auto g = pixel_color.y;
    auto b = pixel_color.z;

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / m_Specification.samplesPerPixel;
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    auto ri = static_cast<uint32_t>(256 * clamp(r, 0.0, 0.999));
    auto gi = static_cast<uint32_t>(256 * clamp(g, 0.0, 0.999));
    auto bi = static_cast<uint32_t>(256 * clamp(b, 0.0, 0.999));

    return 0xff000000 | (bi << 16) | (gi << 8) | ri;
#endif
}

void Renderer::onResize(uint32_t width, uint32_t height)
{
    if (m_finalImage)
    {
        if (m_finalImage->width() == width && m_finalImage->height() == height) return;
        std::lock_guard<std::mutex> guard(m_finalImage->mutex());
        m_finalImage->resize(width, height);
    }
    else
    {
        m_finalImage = createRef<Image>(width, height);
    }

    delete[] m_imageData;
    m_imageData = new uint32_t[m_finalImage->width() * m_finalImage->height()];
}

ref<Image> Renderer::getFinalImage()
{
    return m_finalImage;
}

void Renderer::init(const RendererSpecification& spec)
{
    m_Specification = spec;
}

void Renderer::resetScanlines()
{
    std::lock_guard<std::mutex> guard(m_scanline_mutex);
    m_scanlines = 0;
}

void Renderer::incrementScanlines()
{
    std::lock_guard<std::mutex> guard(m_scanline_mutex);
    m_scanlines++;
}

int Renderer::scanlines()
{
    std::lock_guard<std::mutex> guard(m_scanline_mutex);
    int scanline = m_scanlines;
    return scanline;
}

void Renderer::registerCallback(const ScanlineCallback &callback)
{
    m_callback = callback;
}

void Renderer::abort()
{
    std::lock_guard guard(m_abort_mutex);
    m_shouldAbort = true;
}
}
