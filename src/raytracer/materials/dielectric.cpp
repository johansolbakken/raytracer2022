//
// Created by Johan Solbakken on 7/8/2022.
//

#include "dielectric.h"

#include "raytracer/ray.h"

#include "hittable/hit_record.h"

namespace raytracer
{
	Dielectric::Dielectric(float index_of_refraction) : m_ir(index_of_refraction)
	{
	}

	bool Dielectric::scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const
	{
		attenuation = Color(1.0, 1.0, 1.0);
		float refraction_ratio = rec.front_face ? (1.0 / m_ir) : m_ir;

		Vector3 unit_direction = glm::normalize(r_in.direction());
		float cos_theta = std::fmin(glm::dot(-unit_direction, rec.normal), 1.0);
		float sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
		Vector3 direction;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomfloat())
			direction = reflect(unit_direction, rec.normal);
		else
			direction = refract(unit_direction, rec.normal, refraction_ratio);

		scattered = Ray(rec.p, direction, r_in.time());
		return true;
	}

	float Dielectric::reflectance(float cosine, float ref_idx)
	{
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * std::pow((1 - cosine), 5);
	}

} // raytracer
