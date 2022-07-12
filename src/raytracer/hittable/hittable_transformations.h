#pragma once

#include "hittable.h"

#include "accelerator/aabb.h"

namespace raytracer {

	class Translate : public Hittable {
	public:
		Translate(const ref<Hittable>&  p, const Vector3 & displacement);
		~Translate() override = default;

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		bool boundingBox(double time0, double time1, Aabb& output_box) const override;

	public:
		ref<Hittable> m_object;
		Vector3 m_offset;
	};

	class RotateY : public Hittable {
	public:
		RotateY(const ref<Hittable>& p, double angle);

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		bool boundingBox(double time0, double time1, Aabb& output_box) const override;

	public:
		ref<Hittable> m_object;
		double m_sinTheta;
		double m_cosTheta;
		bool m_hasbox;
		Aabb m_bbox;
	};

}