#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <ostream>
#include "mathutils.h"

namespace raytracer
{
	using Vector3 = glm::vec3;
	using Matrix4 = glm::mat4;
	using Point3 = glm::vec3;
	using Color = glm::vec3;
	using Quaternion = glm::quat;

	inline std::ostream& operator<<(std::ostream& out, const Vector3& v)
	{
		return out << v.x << ' ' << v.y << ' ' << v.z;
	}

	inline float lengthSquared(const Vector3& vec)
	{
		return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	}


	inline Vector3 randomVec3()
	{
		return { randomfloat(), randomfloat(), randomfloat() };
	}

	inline Vector3 randomVec3(float min, float max)
	{
		return { randomfloat(min, max), randomfloat(min, max), randomfloat(min, max) };
	}


	inline Vector3 randomInUnitSpace()
	{
		while (true)
		{
			auto p = randomVec3(-1, 1);
			if (lengthSquared(p) >= 1) continue;
			return p;
		}
	}

	inline Vector3 randomUnitVector()
	{
		return glm::normalize(randomInUnitSpace());
	}

	inline Vector3 randomInHemisphere(const Vector3& normal)
	{
		Vector3 in_unit_sphere = randomInUnitSpace();
		if (glm::dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
			return in_unit_sphere;
		else
			return -in_unit_sphere;
	}

	inline bool nearZero(const Vector3& vec)
	{
		// Return true if the vector is close to zero in all dimensions.
		const auto s = 1e-8;
		return (std::fabs(vec.x) < s) && (std::fabs(vec.y) < s) && (std::fabs(vec.z) < s);
	}

	inline Vector3 reflect(const Vector3& v, const Vector3& n)
	{
		return v - 2 * glm::dot(v, n) * n;
	}

	inline Vector3 refract(const Vector3& uv, const Vector3& n, float etai_over_etat)
	{
		auto cos_theta = std::fmin(dot(-uv, n), 1.0f);
		Vector3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
		Vector3 r_out_parallel = -std::sqrt(std::fabs(1.0f - lengthSquared(r_out_perp))) * n;
		return r_out_perp + r_out_parallel;
	}

	inline Vector3 randomInUnitDisk()
	{
		while (true)
		{
			auto p = Vector3(randomfloat(-1, 1), randomfloat(-1, 1), 0);
			if (lengthSquared(p) >= 1) continue;
			return p;
		}
	}
}
