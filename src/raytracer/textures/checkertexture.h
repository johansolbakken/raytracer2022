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

		CheckerTexture(Color c1, Color c2);

		Color value(float u, float v, const Point3& p) const override;

	public:
		ref<Texture> odd;
		ref<Texture> even{};
	};

} // raytracer
