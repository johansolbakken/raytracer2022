#pragma once

#include "utils/glmutils.h"
#include "hit_record.h"

namespace raytracer
{
	class Ray;
	class Aabb;

	class Hittable
	{
	public:
		virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
		virtual bool boundingBox(double time0, double time1, Aabb& output_box) const = 0;
	};

}


