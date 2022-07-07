#pragma once

#include "material.h"

namespace raytracer
{

	class Metal : public Material
	{
	public:
		explicit Metal(const color& a);

		bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override;

	public:
		color albedo;
	};

} // raytracer
