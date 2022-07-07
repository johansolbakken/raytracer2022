#pragma once

#include <ostream>

#include "utils/glmutils.h"

namespace raytracer
{
	struct Image
	{
		int image_width;
		double aspect_ratio;

		[[nodiscard]] int calculateImageHeight() const
		{
			return static_cast<int>(image_width / aspect_ratio);
		}

	};
}
