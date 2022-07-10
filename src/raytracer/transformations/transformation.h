#pragma once

#include "utils/glmutils.h"

// TODO: rename file to transform

namespace raytracer
{
	class Aabb;
	class Ray;

	class Transform
	{
	public:
		Transform();

		explicit Transform(const Matrix4& matrix);

		Transform(const Matrix4& matrix, const Matrix4& inv);

		static Transform inverse(const Transform& t);

		static Transform translate(const Vector3& delta);

		static Transform scale(float x, float y, float z);

		static Transform rotateX(float angle);

		static Transform rotateY(float angle);

		static Transform rotateZ(float angle);

		static Transform rotate(float angle, const Vector3& axis);

		static Transform LookAt(const Point3& pos, const Point3& look, const Vector3& up);

		Transform operator+(const Transform& other);

		Transform operator*(const Transform& other);

		Point3 operator()(const Vector3& point) const;

		Ray operator()(const Ray& ray) const;

		Aabb operator()(const Aabb& b) const;

		bool operator!=(const Transform& other) const;

		[[nodiscard]] bool swapsHandedness() const;

		[[nodiscard]] Matrix4 matrix() const { return m_matrix; }

	private:
		Matrix4 m_matrix, m_inverse;
	};
}
