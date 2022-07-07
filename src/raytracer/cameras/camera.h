#pragma once

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray;

	struct CameraSpecification
	{
		double aspect_ratio = 16.0 / 9.0;
		double viewport_height = 2.0;
		double focal_length = 1.0;
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

		CameraSpecification m_specification;
	};

}

