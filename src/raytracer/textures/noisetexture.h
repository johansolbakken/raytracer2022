#pragma once

#include "texture.h"
#include "noise/perlin.h"

namespace raytracer
{

	class NoiseTexture : public Texture
	{
	public:
		NoiseTexture() = default;
		explicit NoiseTexture(double sc);

		[[nodiscard]] color value(double u, double v, const point3& p) const override;

	public:
		Perlin m_noise;
		double m_scale{};
	};

} // raytracer
