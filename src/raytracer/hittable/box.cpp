//
// Created by Johan Solbakken on 7/8/2022.
//

#include "box.h"

#include "raytracer/ray.h"

#include "hittable/aarect.h"
#include "hittable/hittablelist.h"

#include "accelerator/aabb.h"

namespace raytracer
{
	Box::Box(const Point3& p0, const Point3& p1, const ref<Material>& ptr)
	{
		box_min = p0;
		box_max = p1;

		sides = createRef<HittableList>();

		sides->add<xy_rect>(p0.x, p1.x, p0.y, p1.y, p1.z, ptr);
		sides->add<xy_rect>(p0.x, p1.x, p0.y, p1.y, p0.z, ptr);

		sides->add<xz_rect>(p0.x, p1.x, p0.z, p1.z, p1.y, ptr);
		sides->add<xz_rect>(p0.x, p1.x, p0.z, p1.z, p0.y, ptr);

		sides->add<yz_rect>(p0.y, p1.y, p0.z, p1.z, p1.x, ptr);
		sides->add<yz_rect>(p0.y, p1.y, p0.z, p1.z, p0.x, ptr);
	}

	bool Box::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		return sides->hit(r, t_min, t_max, rec);
	}

	bool Box::boundingBox(double time0, double time1, Aabb& output_box) const
	{
		output_box = Aabb(box_min, box_max);
		return true;
	}
} // raytracer
