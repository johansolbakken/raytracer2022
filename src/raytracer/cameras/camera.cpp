//
// Created by Johan Solbakken on 7/7/2022.
//

#include "camera.h"

#include "raytracer/ray.h"

namespace raytracer
{
	Ray raytracer::Camera::getRay(double s, double t) const
	{
		vec3 rd = m_lensRadius * randomInUnitDisk();
		vec3 offset = m_u * rd.x + m_v * rd.y;

		auto origin = m_origin + offset;
		auto direction = m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin - offset;
		auto time = randomDouble(m_specification.time0, m_specification.time1);

		return { origin, direction, time};
	}

	Camera::Camera(const raytracer::CameraSpecification& spec)
			: m_specification(spec)
	{
		auto theta = glm::radians(spec.vfov);
		auto h = std::tan(theta / 2);
		auto viewport_height = 2.0 * h;
		auto viewport_width = spec.aspect_ratio * viewport_height;

		m_w = glm::normalize(spec.lookFrom - spec.lookAt);
		m_u = glm::normalize(glm::cross(spec.vup, m_w));
		m_v = glm::cross(m_w, m_u);

		m_origin = spec.lookFrom;
		m_horizontal = spec.focusDistance * viewport_width * m_u;
		m_vertical = spec.focusDistance * viewport_height * m_v;
		m_lowerLeftCorner = m_origin - m_horizontal / 2.0 - m_vertical / 2.0 - spec.focusDistance * m_w;

		m_lensRadius = spec.aperture / 2.0;
	}
}