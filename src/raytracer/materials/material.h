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

		virtual bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const = 0;

		[[nodiscard]] virtual color emitted(float u, float v, const point3& p) const
		{
			return { 0, 0, 0 };
		}
	};

}
