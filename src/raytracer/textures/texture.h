#pragma once

#include "utils/glmutils.h"

namespace raytracer
{

	class Texture
	{
	public:
		virtual ~Texture() = default;

		[[nodiscard]] virtual Color value(float u, float v, const Point3& p) const = 0;
	};

} // raytracer
