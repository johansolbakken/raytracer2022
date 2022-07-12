#include "ray.h"

namespace raytracer
{

	Point3 Ray::origin() const
	{
		return m_origin;
	}

	Ray::Ray(const Point3& origin, const Vector3& direction, double start, double end, double t, int d)
			: m_origin(origin), m_direction(direction), m_mint(start), m_maxt(end), m_time(t), m_depth(d)
	{

	}

	Ray::Ray(const Point3& origin, const Vector3& direction, const Ray& parent, double start, double end)
			: m_origin(origin), m_direction(direction), m_mint(start), m_maxt(end), m_time(parent.time()),
			  m_depth(parent.depth() + 1)
	{

	}

	Vector3 Ray::direction() const
	{
		return m_direction;
	}

	Point3 Ray::at(double t) const
	{
		return m_origin + t * m_direction;
	}

	// Ray of t r(t)
	Point3 Ray::operator()(double t) const
	{
		return at(t);
	}

	double Ray::time() const
	{
		return m_time;
	}

	// minimum time
	double Ray::mint() const
	{
		return m_mint;
	}

	// maximum time
	double Ray::maxt() const
	{
		return m_maxt;
	}

	int Ray::depth() const
	{
		return m_depth;
	}

	void Ray::setTime(double t)
	{
		m_time = t;
	}

	RayDifferential::RayDifferential()
	{
		m_hasDifferential = false;
	}

	RayDifferential::RayDifferential(const Point3& origin, const Vector3& direction, double start, double end, double t,
			int d)
			: Ray(origin, direction, start, end, t, d)
	{
		m_hasDifferential = false;
	}

	RayDifferential::RayDifferential(const Point3& origin, const Vector3& direction, const Ray& parent, double start,
			double end)
			: Ray(origin, direction, parent, start, end)
	{
		m_hasDifferential = false;
	}

	RayDifferential::RayDifferential(const Ray& ray) : Ray(ray)
	{
		m_hasDifferential = false;
	}

	void RayDifferential::scaleDifferentials(double s)
	{
		m_rxOrigin = origin() + (m_rxOrigin - origin()) * s;
		m_ryOrigin = origin() + (m_ryOrigin - origin()) * s;
		m_rxDirection = direction() + (m_rxDirection - direction()) * s;
		m_ryDirection = direction() + (m_ryDirection - direction()) * s;
	}

	bool RayDifferential::hasDifferential() const
	{
		return m_hasDifferential;
	}
}
