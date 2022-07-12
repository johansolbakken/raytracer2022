#include "renderer.h"

#include "raytracer/base.h"
#include "raytracer/image.h"
#include "raytracer/ray.h"

#include "hittable/hittable.h"

#include "cameras/camera.h"

#include "utils/mathutils.h"

#include "materials/material.h"

#include <iostream>

#define cherno 0


namespace raytracer
{
	void Renderer::render(const ref<Hittable>& world, const ref<Camera>& camera)
	{
		m_camera = camera;
		m_world = world;

		resetScanlines();

		if (!m_finalImage || !m_imageData) return;

		for (int y = m_finalImage->height() - 1; y >= 0; y--)
		{
			for (int x = 0; x < m_finalImage->width(); x++)
			{
#if cherno
				// Normalize coordinate
				glm::vec2 coord = {
						(double)x / (double)m_finalImage->width(),
						(double)y / (double)m_finalImage->height()
				};
				coord = coord * 2.0f - 1.0f;
#else
				auto u = double(x) / (m_finalImage->width()-1);
				auto v = double(y) / (m_finalImage->height()-1);
				glm::vec2 coord = { u, v };
#endif
				m_imageData[x + y * m_finalImage->width()] = perPixel(coord);
			}
			incrementScanlines();
			std::cout << scanlines() << std::endl;
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
		if (!world->hit(ray, 0.001, infinity, rec))
			return m_Specification.backgroundColor;

		Ray scattered;
		Color attenuation;
		Color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

		if (!rec.mat_ptr->scatter(ray, rec, attenuation, scattered))
			return emitted;

		return emitted + attenuation * rayColor(scattered, world, depth - 1);
	}

	Renderer::Renderer(const RendererSpecification& spec)
	{
		init(spec);
	}

	uint32_t Renderer::perPixel(glm::vec2 coord)
	{
#if cherno

		//
		//	TODO: solve rest of the quadratic formula to get hit distances
		//	TODO: get coordinate of each hit
		// 	TODO: figure out the normal of each hit

		auto r = (uint8_t)(coord.x*255.0f);
		auto g = (uint8_t(coord.y * 255.0f));

		glm::vec3 rayOrigin(0,0,2.0f);
		glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
		rayDirection = glm::normalize(rayDirection);
		double radius = 0.5f;

		double a = glm::dot(rayDirection, rayDirection);
		double b = 2.0f * glm::dot(rayOrigin, rayDirection);
		double c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

		double descriminant = b * b - 4.0f * a * c;

		if (descriminant >= 0) {

			double t0 = -b - std::sqrt(descriminant) / (2.0f * a);
			double t1 = -b + std::sqrt(descriminant) / (2.0f * a);

			{
				point3 hitPosition = rayOrigin + rayDirection * t0;
			}
			{
				point3 hitPosition = rayOrigin + rayDirection * t1;
			}

			return 0xffff00ff;
		}

		return 0xff000000;
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
}
