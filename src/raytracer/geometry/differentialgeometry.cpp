//
// Created by Johan Solbakken on 09/07/2022.
//

#include "differentialgeometry.h"

namespace raytracer
{

	DifferentialGeometry::DifferentialGeometry()
	{
		u = v = 0.;
		shape = nullptr;
	}

	DifferentialGeometry::DifferentialGeometry(const Point3& point, const Vector3& dpdu, const Vector3& dpdv,
			const Vector3& dndu, const Vector3& dndv, double uu, double vv, const Shape* s)
			: point(point), dPointdu(dpdu), dPointdv(dpdv), dNormaldu(dndu), dNormaldv(dndv)
	{
		// Initialize DifferentialGeometry from parameters
		normalNormalized = glm::normalize(glm::cross(dpdu, dpdv));
		u = uu;
		v = vv;
		shape = s;

		// Adjust normal based on orientation and handedness
		if (shape && (shape->reverseOrientation() ^ shape->transformSwapHandedness()))
			normalNormalized *= -1.0f;
	}
}