//
// Created by Johan Solbakken on 7/8/2022.
//

#include "solidcolor.h"

namespace raytracer
{
	Color SolidColor::value(float u, float v, const Vector3& p) const
	{
		return m_colorValue;
	}

	SolidColor::SolidColor(Color c) : m_colorValue(c)
	{
	}

	SolidColor::SolidColor(float red, float green, float blue)
			: SolidColor(Color(red, green, blue))
	{
	}
} // raytracer
