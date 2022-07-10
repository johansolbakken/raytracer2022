//
// Created by Johan Solbakken on 7/7/2022.
//

#include "lambertian.h"

#include "raytracer/ray.h"

#include "hittable/hit_record.h"
#include "textures/solidcolor.h"

namespace raytracer
{
	bool Lambertian::scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const
	{
		auto scatter_direction = rec.normal + randomUnitVector();

		// Catch degenerate scatter direction
		if (nearZero(scatter_direction))
			scatter_direction = rec.normal;

		scattered = Ray(rec.p, scatter_direction, r_in.time());
		attenuation = m_albedo->value(rec.u, rec.v, rec.p);
		return true;
	}

	Lambertian::Lambertian(const Color& a) : m_albedo(createRef<SolidColor>(a))
	{
	}

	Lambertian::Lambertian(const ref<Texture>& a) : m_albedo(a)
	{

	}
} // raytracer