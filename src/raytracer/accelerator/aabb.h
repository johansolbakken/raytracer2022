#pragma once

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray;

	class Aabb
	{
	public:
		Aabb() = default;
		Aabb(const point3& a, const point3& b);

		[[nodiscard]] point3 minimum() const;
		[[nodiscard]] point3 maximum() const;

		[[nodiscard]] bool hit(const Ray& r, double t_min, double t_max) const;

		static Aabb surroundingBox(const Aabb& box0, const Aabb& box1);

	private:
		point3 m_minimum{};
		point3 m_maximum{};
	};

}
