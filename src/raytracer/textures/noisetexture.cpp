//
// Created by Johan Solbakken on 7/8/2022.
//

#include "noisetexture.h"

namespace raytracer
{
	color NoiseTexture::value(double u, double v, const point3& p) const
	{
		return color(1,1,1) * 0.5 * (1 + sin(m_scale*p.z + 10*m_noise.turb(p)));
	}

	NoiseTexture::NoiseTexture(double sc)
	: m_scale(sc)
	{

	}
} // raytracer