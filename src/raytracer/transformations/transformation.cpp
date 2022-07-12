//
// Created by Johan Solbakken on 09/07/2022.
//

#include "transformation.h"

#include "accelerator/aabb.h"
#include "raytracer/ray.h"


namespace raytracer
{

	Transform::Transform() : m_matrix(1.0), m_inverse(1.0)
	{
	}

	Transform::Transform(const Matrix4& matrix) : m_matrix(matrix), m_inverse(glm::inverse(matrix))
	{
	}

	Transform::Transform(const Matrix4& matrix, const Matrix4& inv) : m_matrix(matrix), m_inverse(inv)
	{
	}


	Transform Transform::inverse(const Transform& t)
	{
		return { t.m_inverse, t.m_matrix };
	}

	Transform Transform::translate(const Vector3& delta)
	{
		auto m = glm::translate(Matrix4(1.0f), delta);
		auto m_inv = glm::translate(Matrix4(1.0f), -delta);
		return { m, m_inv };
	}

	Transform Transform::scale(double x, double y, double z)
	{
		auto m = glm::scale(Matrix4(1.0f), { x, y, z });
		auto m_inv = glm::scale(Matrix4(1.0f), { 1.0 / x, 1.0 / y, 1.0 / z });
		return { m, m_inv };
	}

	Transform Transform::rotateX(double angle)
	{
		auto m = glm::rotate(Matrix4(1.0f), angle, Vector3(1, 0, 0));
		auto inv = glm::transpose(m);
		return { m, inv };
	}

	Transform Transform::rotateY(double angle)
	{
		auto m = glm::rotate(Matrix4(1.0f), angle, Vector3(0, 1, 0));
		auto inv = glm::transpose(m);
		return { m, inv };
	}

	Transform Transform::rotateZ(double angle)
	{
		auto m = glm::rotate(Matrix4(1.0f), angle, Vector3(0, 0, 1));
		auto inv = glm::transpose(m);
		return { m, inv };
	}

	Transform Transform::rotate(double angle, const Vector3& axis)
	{
		auto mat = glm::rotate(Matrix4(1.0f), angle, axis);
		auto inv = glm::transpose(mat);
		return { mat, inv };
	}

	Transform Transform::LookAt(const Point3& pos, const Point3& look, const Vector3& up)
	{
		auto mat = glm::lookAt(pos, look, up);
		auto inv = glm::inverse(mat);
		return { mat, inv };
	}

	Transform Transform::operator+(const Transform& other)
	{
		return { m_matrix + other.m_matrix, m_inverse + other.m_inverse };
	}

	Transform Transform::operator*(const Transform& other)
	{
		auto mat = m_matrix * other.m_matrix;
		auto inv = other.m_inverse * m_inverse;
		return { mat, inv };
	}

	Aabb Transform::operator()(const Aabb& b) const
	{
		const Transform& M = *this;

		Aabb box(M(Point3(b.minimum().x, b.minimum().y, b.minimum().z)));
		box = Aabb::unionPt(box, M(Point3(b.minimum().x, b.minimum().y, b.maximum().z)));
		box = Aabb::unionPt(box, M(Point3(b.minimum().x, b.maximum().y, b.minimum().z)));
		box = Aabb::unionPt(box, M(Point3(b.minimum().x, b.maximum().y, b.maximum().z)));
		box = Aabb::unionPt(box, M(Point3(b.maximum().x, b.minimum().y, b.minimum().z)));
		box = Aabb::unionPt(box, M(Point3(b.maximum().x, b.minimum().y, b.maximum().z)));
		box = Aabb::unionPt(box, M(Point3(b.maximum().x, b.maximum().y, b.minimum().z)));
		box = Aabb::unionPt(box, M(Point3(b.maximum().x, b.maximum().y, b.maximum().z)));

		return box;
	}

	bool Transform::swapsHandedness() const
	{
		return glm::determinant(m_matrix) < 0.f;
	}

	Vector3 Transform::operator()(const Vector3& point) const
	{
		double x = point.x, y = point.y, z = point.z;

		return { m_matrix[0][0] * x + m_matrix[0][1] * y + m_matrix[0][2] * z,
				 m_matrix[1][0] * x + m_matrix[1][1] * y + m_matrix[1][2] * z,
				 m_matrix[2][0] * x + m_matrix[2][1] * y + m_matrix[2][2] * z };
	}

	Ray Transform::operator()(const Ray& ray) const
	{
		const Transform& M = *this;
		return { M(ray.origin()), M(ray.direction()), ray.mint(), ray.maxt(), ray.time(), ray.depth() };
	}

	bool Transform::operator!=(const Transform& other) const
	{
		return m_matrix != other.m_matrix;
	}

}
