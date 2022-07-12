//
// Created by Johan Solbakken on 7/7/2022.
//

#include "metal.h"

#include "raytracer/ray.h"

#include "hittable/hit_record.h"

namespace raytracer
{
	Metal::Metal(const Color& a, double f) : m_albedo(a), m_fuzz(f)
	{
	}

	bool Metal::scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const
	{
		Vector3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
		scattered = Ray(rec.p, reflected + m_fuzz * randomInUnitSpace(), r_in.time());
		attenuation = m_albedo;
		return (glm::dot(scattered.direction(), rec.normal) > 0);
	}

} // raytracer
