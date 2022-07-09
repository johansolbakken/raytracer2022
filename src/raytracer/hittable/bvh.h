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

		BvhNode(const HittableList& list, float time0, float time1);

		BvhNode(const std::vector<ref<Hittable>>& src_objects,
				size_t start, size_t end, float time0, float time1);

		~BvhNode() override = default;

		bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

		bool boundingBox(float time0, float time1, Aabb& output_box) const override;

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

