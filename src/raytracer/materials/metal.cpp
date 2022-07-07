//
// Created by Johan Solbakken on 7/7/2022.
//

#include "metal.h"

#include "raytracer/ray.h"

#include "hittable/hit_record.h"

namespace raytracer
{
	bool Metal::scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const
	{
		vec3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
		scattered = Ray(rec.p, reflected);
		attenuation = albedo;
		return (glm::dot(scattered.direction(), rec.normal) > 0);
	}

	Metal::Metal(const color& a) : albedo(a)
	{
	}
} // raytracer