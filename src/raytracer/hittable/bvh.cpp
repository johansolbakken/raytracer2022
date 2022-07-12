//
// Created by Johan Solbakken on 7/8/2022.
//

#include "bvh.h"

#include "hittable/hittablelist.h"

#include <vector>
#include <algorithm>
#include <iostream>

namespace raytracer
{

	BvhNode::BvhNode(const HittableList& list, double time0, double time1)
			: BvhNode(list.objects(), 0, list.objects().size(), time0, time1)
	{
	}

	BvhNode::BvhNode(const std::vector<ref<Hittable>>& src_objects,
			size_t start, size_t end, double time0, double time1)
	{
		auto objects = src_objects; // Create a modifiable array of the source scene objects

		int axis = randomInt(0,2);
		auto comparator = (axis == 0) ? box_x_compare
									  : (axis == 1) ? box_y_compare
													: box_z_compare;

		size_t object_span = end - start;

		if (object_span == 1) {
			left = right = objects[start];
		} else if (object_span == 2) {
			if (comparator(objects[start], objects[start+1])) {
				left = objects[start];
				right = objects[start+1];
			} else {
				left = objects[start+1];
				right = objects[start];
			}
		} else {
			std::sort(objects.begin() + start, objects.begin() + end, comparator);

			auto mid = start + object_span/2;
			left = createRef<BvhNode>(objects, start, mid, time0, time1);
			right = createRef<BvhNode>(objects, mid, end, time0, time1);
		}

		Aabb box_left, box_right;

		if (  !left->boundingBox(time0, time1, box_left)
			  || !right->boundingBox(time0, time1, box_right)
				)
			std::cerr << "No bounding box in bvh_node constructor.\n";

		box = Aabb::surroundingBox(box_left, box_right);
	}

	bool BvhNode::boundingBox(double time0, double time1, Aabb& output_box) const
	{
		output_box = box;
		return true;
	}

	bool BvhNode::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		if (!box.hit(r, t_min, t_max))
			return false;

		auto hit_left = left->hit(r, t_min, t_max, rec);
		bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

		return hit_left || hit_right;
	}
}
