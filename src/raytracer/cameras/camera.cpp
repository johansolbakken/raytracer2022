//
// Created by Johan Solbakken on 7/7/2022.
//

#include "camera.h"

#include "raytracer/ray.h"

namespace raytracer
{
	Ray raytracer::Camera::getRay(double u, double v) const
	{
		return { m_origin, m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin };
	}

	Camera::Camera(const raytracer::CameraSpecification& spec)
			: m_specification(spec)
	{
		auto viewport_width = spec.aspect_ratio * spec.viewport_height;

		m_origin = point3(0, 0, 0);
		m_horizontal = vec3(viewport_width, 0.0, 0.0);
		m_vertical = vec3(0.0, spec.viewport_height, 0.0);
		m_lowerLeftCorner = m_origin - m_horizontal / 2.0 - m_vertical / 2.0 - vec3(0, 0, spec.focal_length);
	}
}