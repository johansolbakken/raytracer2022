//
// Created by Johan Solbakken on 7/8/2022.
//

#include "solidcolor.h"

namespace raytracer
{
	color SolidColor::value(float u, float v, const vec3& p) const
	{
		return m_colorValue;
	}

	SolidColor::SolidColor(color c) : m_colorValue(c)
	{
	}

	SolidColor::SolidColor(float red, float green, float blue)
			: SolidColor(color(red, green, blue))
	{
	}
} // raytracer
