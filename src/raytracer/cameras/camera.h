#pragma once

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray;

	struct CameraSpecification
	{
		float vfov = 90.0;
		float aspect_ratio = 16.0 / 9.0;
		float aperture = 0.0;
		float focusDistance = 10.0;

		Point3 lookFrom = { 0, 0, 0 };
		Point3 lookAt = { 0, 0, -1 };
		Vector3 vup = { 0, 1, 0 };

		float time0 = 0; // shutter opens
		float time1 = 0; // shutter closes
	};

	class Camera
	{
	public:
		explicit Camera(const CameraSpecification& spec);

		[[nodiscard]] Ray getRay(float u, float v) const;

		void onResize(uint32_t width, uint32_t height);

		float vfov() const
		{
			return m_specification.vfov;
		}

		float aperture() const
		{
			return m_specification.aperture;
		}

		float focusDistance() const
		{
			return m_specification.focusDistance;
		}

		Point3 lookFrom() const
		{
			return m_specification.lookFrom;
		}

		Point3 lookAt() const
		{
			return m_specification.lookAt;
		}

		float time0() const
		{
			return m_specification.time0;
		}

		float time1() const
		{
			return m_specification.time1;
		}

		CameraSpecification specification() const
		{
			return m_specification;
		}

		void init(const CameraSpecification& spec);

	private:
		Point3 m_origin{};
		Point3 m_lowerLeftCorner{};
		Vector3 m_horizontal{};
		Vector3 m_vertical{};
		Vector3 m_u{}, m_v{}, m_w{};

		float m_lensRadius;

		CameraSpecification m_specification;
	};

}

