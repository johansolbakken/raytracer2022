#pragma once
#include "material.h"

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray;

	class Lambertian : public Material
	{
	public:
		explicit Lambertian(const color& a);

		bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override;

	private:
		color m_albedo;
	};

} // raytracer
