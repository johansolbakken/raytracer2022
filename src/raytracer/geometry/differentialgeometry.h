#pragma once

#include "utils/glmutils.h"
#include "shapes/shape.h"

namespace raytracer
{
	struct DifferentialGeometry
	{
		DifferentialGeometry();
		DifferentialGeometry(const Point3& point, const Vector3& dpdu, const Vector3& dpdv,
				const Vector3& dndu, const Vector3& dndv, double uu, double vv, const Shape* s);

		Point3 point{};
		Vector3 normalNormalized{};
		double u, v;
		const Shape* shape;

		Vector3 dPointdu{}, dPointdv{}; // leibniz notation
		Vector3 dNormaldu{}, dNormaldv{};
	};
}

