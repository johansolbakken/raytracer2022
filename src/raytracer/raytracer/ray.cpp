#include "ray.h"

namespace raytracer
{

	point3 Ray::origin() const
	{
		return m_origin;
	}

	Ray::Ray(const point3& origin, const vec3& direction, double time)
			: m_origin(origin), m_direction(direction), m_time(time)
	{
	}

	vec3 Ray::direction() const
	{
		return m_direction;
	}

	point3 Ray::at(double t) const
	{
		return m_origin + t * m_direction;
	}
}