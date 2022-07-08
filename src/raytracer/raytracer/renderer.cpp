#include "renderer.h"

#include "raytracer/base.h"
#include "raytracer/image.h"
#include "raytracer/ray.h"

#include "hittable/hittable.h"

#include "cameras/camera.h"

#include "utils/mathutils.h"

#include "materials/material.h"

#include <iostream>


namespace raytracer
{
	void Renderer::render(const ref<Hittable>& world, const ref<Camera>& camera)
	{
		m_camera = camera;
		m_world = world;

		for (int y = 0; y < m_finalImage->height(); y++)
		{
			for (int x = 0; x < m_finalImage->width(); x++)
			{
				// Normalize coordinate
				glm::vec2 coord = {
						(float)x / (float)m_finalImage->width(),
						(float)y / (float)m_finalImage->height()
				};
				coord = coord * 2.0f - 1.0f;
				m_imageData[x + y * m_finalImage->width()] =  perPixel(coord);;
			}
		}

		m_finalImage->setData(m_imageData);
	}

	color Renderer::rayColor(const Ray& ray, const ref<Hittable>& world, int depth)
	{
		hit_record rec{};

		//
		//	TODO: solve rest of the quadratic formula to get hit distances
		//	TODO: get coordinate of each hit
		// 	TODO: figure out the normal of each hit

		// If we've exceeded the ray bounce limit, no more light is gathered.
		if (depth <= 0)
			return { 0, 0, 0 };

		// If the ray hits nothing, return the background color.
		if (!world->hit(ray, 0.001, infinity, rec))
			return m_Specification.backgroundColor;

		Ray scattered;
		color attenuation;
		color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

		if (!rec.mat_ptr->scatter(ray, rec, attenuation, scattered))
			return emitted;

		return emitted + attenuation * rayColor(scattered, world, depth - 1);
	}

	Renderer::Renderer(const RendererSpecification& spec)
			: m_Specification(spec)
	{

	}

	uint32_t Renderer::perPixel(glm::vec2 coord)
	{
		auto r = (uint8_t)(coord.x*255.0f);
		auto g = (uint8_t(coord.y * 255.0f));

		glm::vec3 rayOrigin(0,0,2.0f);
		glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
		rayDirection = glm::normalize(rayDirection);
		float radius = 0.5f;

		float a = glm::dot(rayDirection, rayDirection);
		float b = 2.0f * glm::dot(rayOrigin, rayDirection);
		float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

		float descriminant = b * b - 4.0f * a * c;
		if (descriminant >= 0) {
			return 0xffff00ff;
		}

		return 0xff000000;
/*
		color pixel_color(0, 0, 0);
		for (int s = 0; s < m_Specification.samplesPerPixel; ++s)
		{
			auto u = (coord.x + randomDouble()) / (m_finalImage->width() - 1);
			auto v = (coord.y + randomDouble()) / (m_finalImage->height() - 1);
			Ray r = m_camera->getRay(u, v);
			pixel_color += rayColor(r, m_world, m_Specification.recursionDepth);
		}

		uint32_t outColor = 0xff000000;

		auto r = pixel_color.x;
		auto g = pixel_color.y;
		auto b = pixel_color.z;

		// Divide the color by the number of samples and gamma-correct for gamma=2.0.
		auto scale = 1.0 / m_Specification.samplesPerPixel;
		r = std::sqrt(scale * r);
		g = std::sqrt(scale * g);
		b = std::sqrt(scale * b);

		// Write the translated [0,255] value of each color component.
		outColor |= static_cast<uint32_t>(256 * clamp(r, 0.0, 0.999));
		outColor |= static_cast<uint32_t>(256 * clamp(g, 0.0, 0.999)) << 8;
		outColor |= static_cast<uint32_t>(256 * clamp(b, 0.0, 0.999)) << 16;

		return outColor;*/
	}

	void Renderer::onResize(uint32_t width, uint32_t height)
	{
		if (m_finalImage)
		{
			if (m_finalImage->width() == width && m_finalImage->height() == height) return;
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
}