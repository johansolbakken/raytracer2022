//
// Created by Johan Solbakken on 7/8/2022.
//

#include "solidcolor.h"

namespace raytracer
{
	color SolidColor::value(double u, double v, const vec3& p) const
	{
		return m_colorValue;
	}

	SolidColor::SolidColor(color c) : m_colorValue(c)
	{
	}

	SolidColor::SolidColor(double red, double green, double blue)
			: SolidColor(color(red, green, blue))
	{
	}
} // raytracer