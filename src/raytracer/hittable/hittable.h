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
		virtual ~Hittable() = default;

		virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;

		virtual bool boundingBox(float time0, float time1, Aabb& output_box) const = 0;
	};

}


