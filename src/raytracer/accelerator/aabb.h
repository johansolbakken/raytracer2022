#pragma once

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray;

	class Aabb
	{
	public:
		Aabb() = default;

		Aabb(const Point3& p);

		Aabb(const Point3& a, const Point3& b);

		[[nodiscard]] Point3 minimum() const;

		[[nodiscard]] Point3 maximum() const;

		[[nodiscard]] bool hit(const Ray& r, float t_min, float t_max) const;

		static Aabb surroundingBox(const Aabb& box0, const Aabb& box1);

		static Aabb unionPt(const Aabb& box, const Point3& pt);

	private:
		Point3 m_minimum{};
		Point3 m_maximum{};
	};

}
