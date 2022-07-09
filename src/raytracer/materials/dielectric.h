#pragma once

#include "materials/material.h"

namespace raytracer
{

	class Dielectric : public Material
	{
	public:
		explicit Dielectric(float index_of_refraction);

		~Dielectric() override = default;

		bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override;

	private:
		static float reflectance(float cosine, float ref_idx);

	private:
		float m_ir;
	};

} // raytracer

