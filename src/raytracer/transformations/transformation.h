#pragma once

#include "utils/glmutils.h"

#include <glm/gtx/transform.hpp>

// TODO: rename file to transform

namespace raytracer
{
	class Aabb;

	using matrix4x4 = glm::mat4;

	class Transform
	{
	public:
		Transform();

		Transform(const matrix4x4& matrix);

		Transform(const matrix4x4& matrix, const matrix4x4& inv);

		static Transform inverse(const Transform& t);

		static Transform translate(const vec3& delta);

		static Transform scale(float x, float y, float z);

		static Transform rotateX(float angle);

		static Transform rotateY(float angle);

		static Transform rotateZ(float angle);

		static Transform rotate(float angle, const vec3& axis);

		static Transform LookAt(const point3& pos, const point3& look, const vec3& up);

		Transform operator+(const Transform& other);

		Transform operator*(const Transform& other);

		Aabb operator()(const Aabb& b) const;

		bool swapsHandedness() const;

	private:
		matrix4x4 m_matrix, m_inverse;
	};
}
