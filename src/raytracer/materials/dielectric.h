#pragma once

#include "materials/material.h"

namespace raytracer
{

	class Dielectric : public Material
	{
	public:
		explicit Dielectric(double index_of_refraction);

		~Dielectric() override = default;

        bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered, double& pdf) const override;

	private:
		static double reflectance(double cosine, double ref_idx);

	private:
		double m_ir;
	};

} // raytracer

