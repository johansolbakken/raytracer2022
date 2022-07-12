#pragma once

#include "hittable.h"

#include "accelerator/aabb.h"

namespace raytracer {

	class Translate : public Hittable {
	public:
		Translate(ref<Hittable>  p, const Vector3 & displacement);
		~Translate() override = default;

		bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

		bool boundingBox(float time0, float time1, Aabb& output_box) const override;

	public:
		ref<Hittable> m_object;
		Vector3 m_offset;
	};

	class RotateY : public Hittable {
	public:
		RotateY(const ref<Hittable>& p, float angle);

		bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

		bool boundingBox(float time0, float time1, Aabb& output_box) const override;

	public:
		ref<Hittable> m_object;
		float m_sinTheta;
		float m_cosTheta;
		bool m_hasbox;
		Aabb m_bbox;
	};

}