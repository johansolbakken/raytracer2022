#pragma once

#include <glm/glm.hpp>
#include <ostream>
#include "mathutils.h"

namespace raytracer
{
	using vec3 = glm::dvec3;
	using point3 = glm::dvec3;
	using color = glm::dvec3;

	inline std::ostream& operator<<(std::ostream& out, const vec3& v)
	{
		return out << v.x << ' ' << v.y << ' ' << v.z;
	}

	inline double lengthSquared(const vec3& vec)
	{
		return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	}


	inline vec3 randomVec3()
	{
		return { randomDouble(), randomDouble(), randomDouble() };
	}

	inline vec3 randomVec3(double min, double max)
	{
		return { randomDouble(min, max), randomDouble(min, max), randomDouble(min, max) };
	}


	inline vec3 randomInUnitSpace()
	{
		while (true)
		{
			auto p = randomVec3(-1, 1);
			if (lengthSquared(p) >= 1) continue;
			return p;
		}
	}

	inline vec3 randomUnitVector()
	{
		return glm::normalize(randomInUnitSpace());
	}

	inline vec3 randomInHemisphere(const vec3& normal)
	{
		vec3 in_unit_sphere = randomInUnitSpace();
		if (glm::dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
			return in_unit_sphere;
		else
			return -in_unit_sphere;
	}

	inline bool nearZero(const vec3& vec)
	{
		// Return true if the vector is close to zero in all dimensions.
		const auto s = 1e-8;
		return (std::fabs(vec.x) < s) && (std::fabs(vec.y) < s) && (std::fabs(vec.z) < s);
	}

	inline vec3 reflect(const vec3& v, const vec3& n)
	{
		return v - 2 * glm::dot(v, n) * n;
	}

	inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
		auto cos_theta = std::fmin(dot(-uv, n), 1.0);
		vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
		vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - lengthSquared(r_out_perp))) * n;
		return r_out_perp + r_out_parallel;
	}

	inline vec3 randomInUnitDisk() {
		while (true) {
			auto p = vec3(randomDouble(-1,1), randomDouble(-1,1), 0);
			if (lengthSquared(p) >= 1) continue;
			return p;
		}
	}
}