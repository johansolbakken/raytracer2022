#pragma once

#include <utility>

#include "material.h"
#include "raytracer/base.h"

namespace raytracer
{
	class Texture;

	class SolidColor;

	class Isotropic : public Material
	{
	public:
		explicit Isotropic(Color c);

		explicit Isotropic(ref<Texture> a);

        bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered, double& pdf) const override;

	public:
		ref<Texture> m_albedo;
	};

} // raytracer
