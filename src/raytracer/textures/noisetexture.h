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

		[[nodiscard]] Color value(double u, double v, const Point3& p) const override;

	public:
		Perlin m_noise;
		double m_scale{};
	};

} // raytracer
