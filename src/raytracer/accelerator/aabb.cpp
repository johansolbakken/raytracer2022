#include "aabb.h"

#include "raytracer/ray.h"

namespace raytracer
{
	bool Aabb::hit(const Ray& r, float t_min, float t_max) const
	{
		for (int a = 0; a < 3; a++)
		{
			auto invD = 1.0f / r.direction()[a];
			auto t0 = (m_minimum[a] - r.origin()[a]) * invD;
			auto t1 = (m_maximum[a] - r.origin()[a]) * invD;
			if (invD < 0.0f)
				std::swap(t0, t1);
			t_min = t0 > t_min ? t0 : t_min;
			t_max = t1 < t_max ? t1 : t_max;
			if (t_max <= t_min)
				return false;
		}
		return true;
	}

	Aabb::Aabb(const point3& a, const point3& b)
	{
		m_minimum = a;
		m_maximum = b;
	}

	point3 Aabb::minimum() const
	{
		return m_minimum;
	}

	point3 Aabb::maximum() const
	{
		return m_maximum;
	}

	Aabb Aabb::surroundingBox(const Aabb& box0, const Aabb& box1)
	{
		point3 small(std::fmin(box0.m_minimum.x, box1.m_minimum.x),
				std::fmin(box0.m_minimum.y, box1.m_minimum.y),
				std::fmin(box0.m_minimum.z, box1.m_minimum.z));

		point3 big(fmax(box0.m_maximum.x, box1.m_maximum.x),
				fmax(box0.m_maximum.y, box1.m_maximum.y),
				fmax(box0.m_maximum.z, box1.m_maximum.z));

		return { small, big };
	}
}
