//
// Created by Johan Solbakken on 7/7/2022.
//

#include "lambertian.h"

#include "raytracer/ray.h"

#include "hittable/hit_record.h"

namespace raytracer
{
	bool Lambertian::scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const
	{
		auto scatter_direction = rec.normal + randomUnitVector();
		scattered = Ray(rec.p, scatter_direction);
		attenuation = m_albedo;
		return true;
	}

	Lambertian::Lambertian(const color& a) : m_albedo(a) {}
} // raytracer