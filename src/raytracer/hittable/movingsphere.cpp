#include "movingsphere.h"

#include "raytracer/ray.h"
#include "hittable/hit_record.h"

namespace raytracer
{

	MovingSphere::MovingSphere(point3 cen0, point3 cen1, double _time0, double _time1, double r, const ref<Material>& m)
			: m_center0(cen0), m_center1(cen1), m_time0(_time0), m_time1(_time1), m_radius(r), m_material(m)
	{}

	bool MovingSphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		vec3 oc = r.origin() - center(r.time());
		auto a = lengthSquared(r.direction());
		auto half_b = glm::dot(oc, r.direction());
		auto c = lengthSquared(oc) - m_radius*m_radius;

		auto discriminant = half_b*half_b - a*c;
		if (discriminant < 0) return false;
		auto sqrtd = std::sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (-half_b - sqrtd) / a;
		if (root < t_min || t_max < root) {
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

	point3 MovingSphere::center(double time) const
	{
		// Linear interpolate?
		return m_center0 + ((time - m_time0) / (m_time1 - m_time0))*(m_center1 - m_center0);
	}
}