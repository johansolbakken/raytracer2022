//
// Created by Johan Solbakken on 7/8/2022.
//

#include "noisetexture.h"

namespace raytracer
{
	Color NoiseTexture::value(double u, double v, const Point3& p) const
	{
		return Color(1, 1, 1) * 0.5 * (1 + std::sin(m_scale * p.z + 10 * m_noise.turb(p)));
	}

	NoiseTexture::NoiseTexture(double sc)
			: m_scale(sc)
	{

	}
} // raytracer
