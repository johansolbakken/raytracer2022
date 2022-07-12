//
// Created by Johan Solbakken on 7/8/2022.
//

#include "solidcolor.h"

namespace raytracer
{
	Color SolidColor::value(double u, double v, const Vector3& p) const
	{
		return m_colorValue;
	}

	SolidColor::SolidColor(Color c) : m_colorValue(c)
	{
	}

	SolidColor::SolidColor(double red, double green, double blue)
			: SolidColor(Color(red, green, blue))
	{
	}
} // raytracer
