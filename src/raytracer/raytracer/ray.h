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

		Ray(const point3& origin, const vec3& direction, double time = 0.0);

		[[nodiscard]] point3 origin() const;

		[[nodiscard]] vec3 direction() const;

		[[nodiscard]] point3 at(double t) const;

		double time() const { return m_time; }

	private:
		point3 m_origin{};
		vec3 m_direction{};
		double m_time;
	};

}


#endif //RAY_RAY_H
