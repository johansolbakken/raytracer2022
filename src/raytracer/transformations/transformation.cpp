//
// Created by Johan Solbakken on 09/07/2022.
//

#include "transformation.h"

#include "accelerator/aabb.h"

namespace raytracer
{

	Transform::Transform() : m_matrix(1.0), m_inverse(1.0)
	{
	}

	Transform::Transform(const matrix4x4& matrix) : m_matrix(matrix), m_inverse(glm::inverse(matrix))
	{
	}

	Transform::Transform(const matrix4x4& matrix, const matrix4x4& inv) : m_matrix(matrix), m_inverse(inv)
	{
	}


	Transform Transform::inverse(const Transform& t)
	{
		return { t.m_inverse, t.m_matrix };
	}

	Transform Transform::translate(const vec3& delta)
	{
		auto m = glm::translate(matrix4x4(1.0f), delta);
		auto m_inv = glm::translate(matrix4x4(1.0f), -delta);
		return { m, m_inv };
	}

	Transform Transform::scale(float x, float y, float z)
	{
		auto m = glm::scale(matrix4x4(1.0f), { x, y, z });
		auto m_inv = glm::scale(matrix4x4(1.0f), { 1.0 / x, 1.0 / y, 1.0 / z });
		return { m, m_inv };
	}

	Transform Transform::rotateX(float angle)
	{
		auto m = glm::rotate(matrix4x4(1.0f), angle, vec3(1, 0, 0));
		auto inv = glm::transpose(m);
		return { m, inv };
	}

	Transform Transform::rotateY(float angle)
	{
		auto m = glm::rotate(matrix4x4(1.0f), angle, vec3(0, 1, 0));
		auto inv = glm::transpose(m);
		return { m, inv };
	}

	Transform Transform::rotateZ(float angle)
	{
		auto m = glm::rotate(matrix4x4(1.0f), angle, vec3(0, 0, 1));
		auto inv = glm::transpose(m);
		return { m, inv };
	}

	Transform Transform::rotate(float angle, const vec3& axis)
	{
		auto mat = glm::rotate(matrix4x4(1.0f), angle, axis);
		auto inv = glm::transpose(mat);
		return { mat, inv };
	}

	Transform Transform::LookAt(const point3& pos, const point3& look, const vec3& up)
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
		Aabb box(b);
		return box;
	}

	bool Transform::swapsHandedness() const
	{
		return glm::determinant(m_matrix) < 0.f;
	}

}
