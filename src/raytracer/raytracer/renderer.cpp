#include "renderer.h"

#include "raytracer/base.h"
#include "raytracer/image.h"
#include "raytracer/ray.h"

#include "hittable/hittable.h"

#include "cameras/camera.h"

#include "utils/mathutils.h"

#include <iostream>


namespace raytracer
{
	void Renderer::render(Image& image, const ref<Hittable>& world, const ref<Camera>& camera)
	{
		auto& buffer = m_Specification.buffer;

		const auto aspect_ratio = image.aspect_ratio;
		const int image_width = image.image_width;
		const int image_height = image.calculateImageHeight();
		const int samplesPerPixel = m_Specification.samplesPerPixel;
		const int recursionDepth = m_Specification.recursionDepth;

		// Camera
		auto viewport_height = 2.0;
		auto viewport_width = aspect_ratio * viewport_height;
		auto focal_length = 1.0;

		auto origin = point3(0, 0, 0);
		auto horizontal = vec3(viewport_width, 0, 0);
		auto vertical = vec3(0, viewport_height, 0);
		auto lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - vec3(0, 0, focal_length);

		// Render

		buffer << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j = image_height - 1; j >= 0; --j)
		{
			std::cout << "\rScanlines remaining: " << j << std::flush;

			for (int i = 0; i < image_width; ++i)
			{
				color pixel_color(0, 0, 0);
				for (int s = 0; s < samplesPerPixel; ++s)
				{
					auto u = (i + randomDouble()) / (image_width - 1);
					auto v = (j + randomDouble()) / (image_height - 1);
					Ray r = camera->getRay(u, v);
					pixel_color += rayColor(r, world, recursionDepth);
				}
				writeColor(buffer, pixel_color, samplesPerPixel);
			}
		}

		std::cout << "\nDone.\n";
	}

	void Renderer::writeColor(std::ostream& out, color pixelColor, int samplesPerPixel)
	{
		auto r = pixelColor.x;
		auto g = pixelColor.y;
		auto b = pixelColor.z;

		// Divide the color by the number of samples and gamma-correct for gamma=2.0.
		auto scale = 1.0 / samplesPerPixel;
		r = std::sqrt(scale * r);
		g = std::sqrt(scale * g);
		b = std::sqrt(scale * b);

		// Write the translated [0,255] value of each color component.
		out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
	}

	color Renderer::rayColor(const Ray& ray, const ref<Hittable>& world, int depth)
	{
		hit_record rec{};

		// If we've exceeded the ray bounce limit, no more light is gathered.
		if (depth <= 0)
			return {0, 0, 0};

		if (world->hit(ray, 0.001, infinity, rec))
		{
			point3 target = rec.p + randomInHemisphere(rec.normal);
			return 0.5 * rayColor(Ray(rec.p, target - rec.p), world, depth - 1);
		}

		vec3 unit_direction = glm::normalize(ray.direction());
		auto t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
	}

	Renderer::Renderer(const RendererSpecification& spec)
	: m_Specification(spec)
	{

	}
}