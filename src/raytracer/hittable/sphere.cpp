//
// Created by Johan Solbakken on 7/7/2022.
//

#include "sphere.h"

#include <utility>

#include "raytracer/ray.h"

#include "accelerator/aabb.h"

namespace raytracer
{
	Sphere::Sphere(raytracer::point3 cen, float r, raytracer::ref<raytracer::Material> material)
			: m_center(cen), m_radius(r), m_material(std::move(material))
	{
	}

	bool Sphere::hit(const raytracer::Ray& r, float t_min, float t_max, raytracer::hit_record& rec) const
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

		auto[u, v] = getSphereUv(outward_normal);
		rec.u = u;
		rec.v = v;

		return true;
	}

	bool Sphere::boundingBox(float time0, float time1, Aabb& output_box) const
	{
		output_box = Aabb(
				m_center - vec3(m_radius, m_radius, m_radius),
				m_center + vec3(m_radius, m_radius, m_radius)
		);
		return true;
	}

	std::pair<float, float> Sphere::getSphereUv(const point3& p)
	{
		// p: a given point on the sphere of radius one, centered at the origin.
		// u: returned value [0,1] of angle around the Y axis from X=-1.
		// v: returned value [0,1] of angle from Y=-1 to Y=+1.
		//     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
		//     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
		//     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

		auto theta = std::acos(-p.y);
		auto phi = atan2(-p.z, p.x) + M_PI;

		auto u = phi / (2 * M_PI);
		auto v = theta / M_PI;
		return { u, v };
	}


}
