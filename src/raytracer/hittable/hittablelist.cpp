//
// Created by Johan Solbakken on 7/7/2022.
//

#include "hittablelist.h"

#include "accelerator/aabb.h"

namespace raytracer
{

	bool HittableList::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const
	{
		hit_record temp_rec{};
		bool hit_anything = false;
		auto closest_so_far = t_max;

		for (const auto& object: m_objects)
		{
			if (object->hit(r, t_min, closest_so_far, temp_rec))
			{
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}

		return hit_anything;
	}

	void HittableList::add(const ref<Hittable>& object)
	{
		m_objects.push_back(object);
	}

	void HittableList::clear()
	{
		m_objects.clear();
	}

	HittableList::HittableList(const ref<Hittable>& object)
	{
		add(object);
	}

	bool HittableList::boundingBox(float time0, float time1, Aabb& output_box) const
	{
		if (m_objects.empty()) return false;

		Aabb temp_box;
		bool first_box = true;

		for (const auto& object: m_objects)
		{
			if (!object->boundingBox(time0, time1, temp_box)) return false;
			output_box = first_box ? temp_box : Aabb::surroundingBox(output_box, temp_box);
			first_box = false;
		}

		return true;
	}

}
