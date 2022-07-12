#pragma once

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray;

	struct hit_record;

	class Material
	{
	public:
		virtual ~Material() = default;

		virtual bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const = 0;

		[[nodiscard]] virtual Color emitted(double u, double v, const Point3& p) const
		{
			return { 0, 0, 0 };
		}
	};

}
