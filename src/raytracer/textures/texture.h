#pragma once

#include "utils/glmutils.h"

namespace raytracer
{

	class Texture
	{
	public:
		virtual ~Texture() = default;
		[[nodiscard]] virtual color value(double u, double v, const point3& p) const = 0;
	};

} // raytracer
