#pragma once

#include "material.h"

namespace raytracer
{

	class Metal : public Material
	{
	public:
		explicit Metal(const color& a, float f = 0.0f);

		~Metal() override = default;

		bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override;

	public:
		color m_albedo;
		float m_fuzz;
	};

} // raytracer
