#pragma once

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray;

	struct CameraSpecification
	{
		double vfov=90.0;
		double aspect_ratio = 16.0 / 9.0;
		double aperture = 0.01;
		double focusDistance = 1.0;

		point3 lookFrom={0,0,0};
		point3 lookAt={0,0,-1};
		vec3 vup={0,1,0};
	};

	class Camera
	{
	public:
		explicit Camera(const CameraSpecification& spec);

		[[nodiscard]] Ray getRay(double u, double v) const;

	private:
		point3 m_origin{};
		point3 m_lowerLeftCorner{};
		vec3 m_horizontal{};
		vec3 m_vertical{};
		vec3 m_u{}, m_v{}, m_w{};

		double m_lensRadius;

		CameraSpecification m_specification;
	};

}

