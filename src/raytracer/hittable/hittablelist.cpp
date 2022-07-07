//
// Created by Johan Solbakken on 7/7/2022.
//

#include "hittablelist.h"

namespace raytracer
{

	bool HittableList::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		hit_record temp_rec{};
		bool hit_anything = false;
		auto closest_so_far = t_max;

		for (const auto& object : objects) {
			if (object->hit(r, t_min, closest_so_far, temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}

		return hit_anything;
	}

	void HittableList::add(const ref<Hittable>& object)
	{
		objects.push_back(object);
	}

	void HittableList::clear()
	{
		objects.clear();
	}

	HittableList::HittableList(const ref<Hittable>& object)
	{
		add(object);
	}

}