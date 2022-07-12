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
	public:
		BvhNode() = default;

		BvhNode(const HittableList& list, double time0, double time1);

		BvhNode(
				const std::vector<ref<Hittable>>& src_objects,
		size_t start, size_t end, double time0, double time1);

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		bool boundingBox(double time0, double time1, Aabb& output_box) const override;

	public:
		ref<Hittable> left;
		ref<Hittable> right;
		Aabb box;
	};

	inline bool box_compare(const ref<Hittable> a, const ref<Hittable> b, int axis) {
		Aabb box_a;
		Aabb box_b;

		if (!a->boundingBox(0,0, box_a) || !b->boundingBox(0,0, box_b))
			std::cerr << "No bounding box in bvh_node constructor.\n";

		auto a_min = box_a.minimum();
		auto b_min = box_b.minimum();

		if (axis == 0) {
			return a_min.x < b_min.x;
		} else if (axis == 1) {
			return a_min.y < b_min.y;
		} else {
			return a_min.z < b_min.z;
		}
	}


	inline bool box_x_compare (const ref<Hittable> a, const ref<Hittable> b) {
		return box_compare(a, b, 0);
	}

	inline bool box_y_compare (const ref<Hittable> a, const ref<Hittable> b) {
		return box_compare(a, b, 1);
	}

	inline bool box_z_compare (const ref<Hittable> a, const ref<Hittable> b) {
		return box_compare(a, b, 2);
	}
}

