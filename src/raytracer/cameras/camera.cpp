//
// Created by Johan Solbakken on 7/7/2022.
//

#include "camera.h"

#include "raytracer/ray.h"

namespace raytracer
{
	Ray Camera::getRay(double s, double t) const
	{
		Vector3 rd = m_lensRadius * randomInUnitDisk();
		Vector3 offset = m_u * rd.x + m_v * rd.y;

		auto origin = m_origin + offset;
		auto direction = m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin - offset;
		auto time = randomdouble(m_specification.time0, m_specification.time1);

		Ray ray(origin, direction, 0.00);
		ray.setTime(time);

		return ray;
	}

	Camera::Camera(const CameraSpecification &spec)
	{
		init(spec);
	}

	void Camera::init(const CameraSpecification &spec)
	{
		m_specification = spec;
		update();
	}

	void Camera::onResize(uint32_t width, uint32_t height)
	{
		CameraSpecification spec(m_specification);
		spec.aspect_ratio = (double)width / (double)height;

		init(spec);
	}

	void Camera::update()
	{
		auto theta = glm::radians(m_specification.vfov);
		auto h = std::tan(theta / 2.0);
		auto viewport_height = 2.0 * h;
		auto viewport_width = m_specification.aspect_ratio * viewport_height;

		m_w = glm::normalize(m_specification.lookFrom - m_specification.lookAt);
		m_u = glm::normalize(glm::cross(m_specification.vup, m_w));
		m_v = glm::normalize(glm::cross(m_w, m_u));

		// TODO: Rename CameraSpecification::lookFrom to origin
		m_origin = m_specification.lookFrom;
		m_horizontal = m_specification.focusDistance * viewport_width * m_u;
		m_vertical = m_specification.focusDistance * viewport_height * m_v;
		m_lowerLeftCorner = m_origin - m_horizontal / 2.0 - m_vertical / 2.0 - m_specification.focusDistance * m_w;

		m_lensRadius = m_specification.aperture / 2.0;
	}

	void Camera::setPosition(const Vector3 &pos)
	{
		m_specification.lookFrom = pos;
	}

	void Camera::setLookAt(const Vector3 &lookAt)
	{
		m_specification.lookAt = lookAt;
	}

	void Camera::setUp(const Vector3 &up)
	{
		m_specification.vup = up;
	}

	void Camera::setAspectRatio(double aspect)
	{
		m_specification.aspect_ratio = aspect;
	}
}
