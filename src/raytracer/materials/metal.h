#pragma once

#include "material.h"

namespace raytracer
{

	class Metal : public Material
	{
	public:
		explicit Metal(const Color& a, float f = 0.0f);

		~Metal() override = default;

		bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const override;

	public:
		Color m_albedo;
		float m_fuzz;
	};

} // raytracer
