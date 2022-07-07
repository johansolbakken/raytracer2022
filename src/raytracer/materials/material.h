#pragma once

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray;

	struct hit_record;

	class Material
	{
	public:
		virtual bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const = 0;
	};

}
