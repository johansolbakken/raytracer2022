//
// Created by Johan Solbakken on 7/7/2022.
//

#include "sphere.h"

#include <utility>

#include "raytracer/ray.h"

#include "accelerator/aabb.h"

namespace raytracer
{
	Sphere::Sphere(raytracer::point3 cen, double r, raytracer::ref<raytracer::Material> material)
			: m_center(cen), m_radius(r), m_material(std::move(material))
	{
	}

	bool Sphere::hit(const raytracer::Ray& r, double t_min, double t_max, raytracer::hit_record& rec) const
	{
		vec3 oc = r.origin() - m_center;
		auto a = lengthSquared(r.direction());
		auto half_b = dot(oc, r.direction());
		auto c = lengthSquared(oc) - m_radius * m_radius;

		auto discriminant = half_b * half_b - a * c;
		if (discriminant < 0) return false;
		auto sqrtd = sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (-half_b - sqrtd) / a;
		if (root < t_min || t_max < root)
		{
			root = (-half_b + sqrtd) / a;
			if (root < t_min || t_max < root)
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		rec.normal = (rec.p - m_center) / m_radius;
		vec3 outward_normal = (rec.p - m_center) / m_radius;
		rec.setFaceNormal(r, outward_normal);
		rec.mat_ptr = m_material;

		return true;
	}

	bool Sphere::boundingBox(double time0, double time1, Aabb& output_box) const
	{
		output_box = Aabb(
				m_center - vec3(m_radius, m_radius, m_radius),
				m_center + vec3(m_radius, m_radius, m_radius)
		);
		return true;
	}


}