#pragma once

#include "texture.h"
#include "raytracer/base.h"

namespace raytracer
{

	class CheckerTexture : public Texture
	{
	public:
		CheckerTexture()
		{
		}

		CheckerTexture(ref<Texture> _even, ref<Texture> _odd);

		CheckerTexture(color c1, color c2);

		color value(float u, float v, const point3& p) const override;

	public:
		ref<Texture> odd;
		ref<Texture> even{};
	};

} // raytracer
