#include "hittable_transformations.h"

#include "raytracer/ray.h"

#include "accelerator/aabb.h"

#include <utility>

namespace raytracer
{
	Translate::Translate(const ref<Hittable>& p,
			const raytracer::Vector3& displacement)
			: m_object(p), m_offset(displacement)
	{
	}

	bool Translate::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		Ray moved_r(r.origin() - m_offset, r.direction(), r.time());
		if (!m_object->hit(moved_r, t_min, t_max, rec))
			return false;

		rec.p += m_offset;
		rec.setFaceNormal(moved_r, rec.normal);

		return true;
	}

	bool Translate::boundingBox(double time0, double time1, Aabb& output_box) const
	{
		if (!m_object->boundingBox(time0, time1, output_box))
			return false;

		output_box = Aabb(
				output_box.minimum() + m_offset,
				output_box.maximum() + m_offset);

		return true;
	}

	RotateY::RotateY(const ref<Hittable>& p, double angle)
	: m_object(p)
	{
		m_bbox = Aabb();
		auto radians = glm::radians(angle);
		m_sinTheta = std::sin(radians);
		m_cosTheta = std::cos(radians);
		m_hasbox = m_object->boundingBox(0, 1, m_bbox);

        Point3 min( math::infinity,  math::infinity,  math::infinity);
        Point3 max(-math::infinity, -math::infinity, -math::infinity);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					auto x = double(i)*m_bbox.maximum().x + (1.0f-double(i)) * m_bbox.minimum().x;
					auto y = double(j)*m_bbox.maximum().y + (1.0f-double(j)) * m_bbox.minimum().y;
					auto z = double(k)*m_bbox.maximum().z + (1.0f-double(k)) * m_bbox.minimum().z;

					auto newx =  m_cosTheta*x + m_sinTheta*z;
					auto newz = -m_sinTheta*x + m_cosTheta*z;

					Vector3 tester(newx, y, newz);

					for (int c = 0; c < 3; c++) {
						min[c] = std::fmin(min[c], tester[c]);
						max[c] = std::fmax(max[c], tester[c]);
					}
				}
			}
		}

		m_bbox = Aabb(min, max);
	}

	bool RotateY::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		auto origin = r.origin();
		auto direction = r.direction();

		origin[0] = m_cosTheta*r.origin()[0] - m_sinTheta*r.origin()[2];
		origin[2] = m_sinTheta*r.origin()[0] + m_cosTheta*r.origin()[2];

		direction[0] = m_cosTheta*r.direction()[0] - m_sinTheta*r.direction()[2];
		direction[2] = m_sinTheta*r.direction()[0] + m_cosTheta*r.direction()[2];

		Ray rotated_r(origin, direction, r.time());

		if (!m_object->hit(rotated_r, t_min, t_max, rec))
			return false;

		auto p = rec.p;
		auto normal = rec.normal;

		p[0] =  m_cosTheta*rec.p[0] + m_sinTheta*rec.p[2];
		p[2] = -m_sinTheta*rec.p[0] + m_cosTheta*rec.p[2];

		normal[0] =  m_cosTheta*rec.normal[0] + m_sinTheta*rec.normal[2];
		normal[2] = -m_sinTheta*rec.normal[0] + m_cosTheta*rec.normal[2];

		rec.p = p;
		rec.setFaceNormal(rotated_r, normal);

		return true;
	}

	bool RotateY::boundingBox(double time0, double time1, Aabb& output_box) const
	{
		output_box = m_bbox;
		return m_hasbox;
	}
}
