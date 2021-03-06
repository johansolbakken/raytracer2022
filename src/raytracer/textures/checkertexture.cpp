//
// Created by Johan Solbakken on 7/8/2022.
//

#include "checkertexture.h"

#include <utility>

#include "textures/solidcolor.h"

namespace raytracer
{
	CheckerTexture::CheckerTexture(ref<Texture> _even, ref<Texture> _odd)
			: even(std::move(_even)), odd(std::move(_odd))
	{
	}

	CheckerTexture::CheckerTexture(Color c1, Color c2)
			: even(createRef<SolidColor>(c1)), odd(createRef<SolidColor>(c2))
	{
	}

	Color CheckerTexture::value(double u, double v, const Point3& p) const
	{
		auto sines = std::sin(10 * p.x) * std::sin(10 * p.y) * std::sin(10 * p.z);
		if (sines < 0)
			return odd->value(u, v, p);
		else
			return even->value(u, v, p);
	}


} // raytracer
