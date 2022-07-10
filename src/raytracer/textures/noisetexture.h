#pragma once

#include "texture.h"
#include "noise/perlin.h"

namespace raytracer
{

	class NoiseTexture : public Texture
	{
	public:
		NoiseTexture() = default;

		explicit NoiseTexture(float sc);

		[[nodiscard]] Color value(float u, float v, const Point3& p) const override;

	public:
		Perlin m_noise;
		float m_scale{};
	};

} // raytracer
