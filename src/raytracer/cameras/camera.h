#pragma once

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray;

	struct CameraSpecification
	{
		double vfov = 90.0;
		double aspect_ratio = 16.0 / 9.0;
		double aperture = 0.0;
		double focusDistance = 10.0;

		Point3 lookFrom = {0, 0, 0};
		Point3 lookAt = {0, 0, -1};
		Vector3 vup = {0, 1, 0};

		double time0 = 0; // shutter opens
		double time1 = 0; // shutter closes
	};

	class Camera
	{
	public:
		Camera() = default;
		explicit Camera(const CameraSpecification &spec);
		virtual ~Camera() = default;

		[[nodiscard]] Ray getRay(double u, double v) const;

		void onResize(uint32_t width, uint32_t height);

		double vfov() const
		{
			return m_specification.vfov;
		}

		double aperture() const
		{
			return m_specification.aperture;
		}

		double focusDistance() const
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

		double time0() const
		{
			return m_specification.time0;
		}

		double time1() const
		{
			return m_specification.time1;
		}

		CameraSpecification specification() const
		{
			return m_specification;
		}

		void init(const CameraSpecification &spec);
		void update();

		void setPosition(const Vector3& pos);
		void setLookAt(const Vector3& lookAt);
		void setUp(const Vector3& up);
		void setAspectRatio(double aspect);

		Point3 origin() const { return m_origin; }

	private:
		Point3 m_origin{};
		Point3 m_lowerLeftCorner{};
		Vector3 m_horizontal{};
		Vector3 m_vertical{};
		Vector3 m_u{}, m_v{}, m_w{};

		double m_lensRadius;

		CameraSpecification m_specification;
	};
}
