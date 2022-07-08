#pragma once

#include <iostream>
#include "hittable.h"

#include "accelerator/aabb.h"

namespace raytracer
{
	class HittableList;

	class BvhNode : public Hittable
	{
	public:
		BvhNode() = default;

		BvhNode(const HittableList& list, double time0, double time1);

		BvhNode(const std::vector<ref<Hittable>>& src_objects,
				size_t start, size_t end, double time0, double time1);

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		bool boundingBox(double time0, double time1, Aabb& output_box) const override;

	public:
		ref<Hittable> m_left;
		ref<Hittable> m_right;
		Aabb m_box;
	};

	bool boxCompare(const ref<Hittable>& a, const ref<Hittable>& b, int axis);

	bool boxXCompare(const ref<Hittable>& a, const ref<Hittable>& b);

	bool boxYCompare(const ref<Hittable>& a, const ref<Hittable>& b);

	bool boxZCompare(const ref<Hittable>& a, const ref<Hittable>& b);
}

