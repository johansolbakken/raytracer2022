#pragma once

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray
	{
	public:
		Ray() = default;

		Ray(const Point3 &origin,
			const Vector3 &direction,
			double start,
			double end = math::infinity,
			double t = 0.f,
			int d = 0);

		Ray(const Point3 &origin,
			const Vector3 &direction,
			const Ray &parent,
			double start,
			double end = math::infinity);

		[[nodiscard]] Point3 at(double t) const;

		[[nodiscard]] Point3 operator()(double t) const;

		[[nodiscard]] Point3 origin() const;

		[[nodiscard]] Vector3 direction() const;

		[[nodiscard]] double time() const;

		[[nodiscard]] double mint() const;

		[[nodiscard]] double maxt() const;

		[[nodiscard]] int depth() const;

		void setTime(double t);

		void setOrigin(const Point3 &origin) { m_origin = origin; }
		void setDirection(const Vector3 &direction) { m_direction = direction; }

	private:
		Point3 m_origin{};
		Vector3 m_direction{};
		double m_time{};
		mutable double m_mint{}, m_maxt{};
		int m_depth{};
	};

	class RayDifferential : public Ray
	{
	public:
		explicit RayDifferential();

		explicit RayDifferential(const Point3 &origin, const Vector3 &direction, double start, double end = math::infinity,
								 double t = 0.f, int d = 0);

		explicit RayDifferential(const Point3 &origin, const Vector3 &direction, const Ray &parent, double start,
								 double end = math::infinity);

		explicit RayDifferential(const Ray &ray);

		void scaleDifferentials(double s);

		bool hasDifferential() const;

	private:
		bool m_hasDifferential;
		Point3 m_rxOrigin{}, m_ryOrigin{};
		Vector3 m_rxDirection{}, m_ryDirection{};
	};

}
