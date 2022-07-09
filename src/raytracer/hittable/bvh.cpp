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

	BvhNode::BvhNode(const HittableList& list, float time0, float time1)
			: BvhNode(list.objects(), 0, list.objects().size(), time0, time1)
	{
	}

	BvhNode::BvhNode(const std::vector<ref<Hittable>>& src_objects,
			size_t start, size_t end, float time0, float time1)
	{
		auto objects = src_objects; // Create a modifiable array of the source scene objects

		int axis = randomInt(0, 2);
		auto comparator = (axis == 0) ? boxXCompare
									  : (axis == 1) ? boxYCompare
													: boxZCompare;

		size_t object_span = end - start;

		if (object_span == 1)
		{
			m_left = m_right = objects[start];
		}
		else if (object_span == 2)
		{
			if (comparator(objects[start], objects[start + 1]))
			{
				m_left = objects[start];
				m_right = objects[start + 1];
			}
			else
			{
				m_left = objects[start + 1];
				m_right = objects[start];
			}
		}
		else
		{
			std::sort(objects.begin() + start, objects.begin() + end, comparator);

			auto mid = start + object_span / 2;
			m_left = createRef<BvhNode>(objects, start, mid, time0, time1);
			m_right = createRef<BvhNode>(objects, mid, end, time0, time1);
		}

		Aabb box_left, box_right;

		if (!m_left->boundingBox(time0, time1, box_left)
			|| !m_right->boundingBox(time0, time1, box_right)
				)
			std::cout << "No bounding box in bvh_node constructor.\n";

		m_box = Aabb::surroundingBox(box_left, box_right);
	}

	bool BvhNode::boundingBox(float time0, float time1, Aabb& output_box) const
	{
		output_box = m_box;
		return true;
	}

	bool BvhNode::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const
	{
		if (!m_box.hit(r, t_min, t_max))
			return false;

		bool hit_left = m_left->hit(r, t_min, t_max, rec);
		bool hit_right = m_right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

		return hit_left || hit_right;
	}

	bool boxCompare(const ref<Hittable>& a, const ref<Hittable>& b, int axis)
	{
		Aabb box_a;
		Aabb box_b;

		if (!a->boundingBox(0, 0, box_a) || !b->boundingBox(0, 0, box_b))
			std::cout << "No bounding box in bvh_node constructor.\n";

		return box_a.minimum()[axis] < box_b.maximum()[axis];
	}

	bool boxXCompare(const ref<Hittable>& a, const ref<Hittable>& b)
	{
		return boxCompare(a, b, 0);
	}

	bool boxYCompare(const ref<Hittable>& a, const ref<Hittable>& b)
	{
		return boxCompare(a, b, 1);
	}

	bool boxZCompare(const ref<Hittable>& a, const ref<Hittable>& b)
	{
		return boxCompare(a, b, 2);
	}
}
