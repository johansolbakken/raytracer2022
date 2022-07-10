#include "movingsphere.h"

#include "raytracer/ray.h"
#include "hittable/hit_record.h"
#include "accelerator/aabb.h"

namespace raytracer
{

	MovingSphere::MovingSphere(Point3 cen0, Point3 cen1, float _time0, float _time1, float r, const ref<Material>& m)
			: m_center0(cen0), m_center1(cen1), m_time0(_time0), m_time1(_time1), m_radius(r), m_material(m)
	{
	}

	bool MovingSphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const
	{
		Vector3 oc = r.origin() - center(r.time());
		auto a = lengthSquared(r.direction());
		auto half_b = glm::dot(oc, r.direction());
		auto c = lengthSquared(oc) - m_radius * m_radius;

		auto discriminant = half_b * half_b - a * c;
		if (discriminant < 0) return false;
		auto sqrtd = std::sqrt(discriminant);

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
		auto outward_normal = (rec.p - center(r.time())) / m_radius;
		rec.setFaceNormal(r, outward_normal);
		rec.mat_ptr = m_material;

		return true;
	}

	Point3 MovingSphere::center(float time) const
	{
		// Linear interpolate?
		return m_center0 + ((time - m_time0) / (m_time1 - m_time0)) * (m_center1 - m_center0);
	}

	bool MovingSphere::boundingBox(float time0, float time1, Aabb& output_box) const
	{
		Aabb box0(
				center(time0) - Vector3(m_radius, m_radius, m_radius),
				center(time0) + Vector3(m_radius, m_radius, m_radius));
		Aabb box1(
				center(time1) - Vector3(m_radius, m_radius, m_radius),
				center(time1) + Vector3(m_radius, m_radius, m_radius));
		output_box = Aabb::surroundingBox(box0, box1);
		return true;
	}
}
