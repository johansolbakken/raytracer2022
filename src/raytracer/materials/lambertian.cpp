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

		// Catch degenerate scatter direction
		if (nearZero(scatter_direction))
			scatter_direction = rec.normal;

		scattered = Ray(rec.p, scatter_direction, r_in.time());
		attenuation = m_albedo;
		return true;
	}

	Lambertian::Lambertian(const color& a) : m_albedo(a)
	{
	}
} // raytracer