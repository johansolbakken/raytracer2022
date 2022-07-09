//
// Created by Johan Solbakken on 7/7/2022.
//

#ifndef RAY_RAY_H
#define RAY_RAY_H

#include "utils/glmutils.h"

namespace raytracer
{

	class Ray
	{
	public:
		Ray() = default;

		Ray(const point3& origin, const vec3& direction, float start, float end = infinity, float t = 0.f,
				int d = 0);

		Ray(const point3& origin, const vec3& direction, const Ray& parent, float start, float end = infinity);

		[[nodiscard]] point3 at(float t) const;

		[[nodiscard]] point3 operator()(float t) const;

		[[nodiscard]] point3 origin() const;

		[[nodiscard]] vec3 direction() const;

		[[nodiscard]] float time() const;

		[[nodiscard]] float mint() const;

		[[nodiscard]] float maxt() const;

		[[nodiscard]] int depth() const;

		void setTime(float t);


	private:
		point3 m_origin{};
		vec3 m_direction{};
		float m_time{};
		mutable float m_mint{}, m_maxt{};
		int m_depth{};
	};

	class RayDifferential : public Ray
	{
	public:
		explicit RayDifferential();

		explicit RayDifferential(const point3& origin, const vec3& direction, float start, float end = infinity,
				float t = 0.f, int d = 0);

		explicit RayDifferential(const point3& origin, const vec3& direction, const Ray& parent, float start,
				float end = infinity);

		explicit RayDifferential(const Ray& ray);

		void scaleDifferentials(float s);

		bool hasDifferential() const;

	private:
		bool m_hasDifferential;
		point3 m_rxOrigin{}, m_ryOrigin{};
		vec3 m_rxDirection{}, m_ryDirection{};
	};

}


#endif //RAY_RAY_H
