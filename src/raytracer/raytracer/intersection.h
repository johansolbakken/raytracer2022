#pragma once

#include "geometry/differentialgeometry.h"
#include "primitives/primitive.h"
#include "transformations/transformation.h"

namespace raytracer
{
	struct Intersection
	{

		DifferentialGeometry dg;
		const Primitive* primitive{};
		Transform worldToObject, objectToWorld;
		uint32_t shapeId{}, primitiveId{};
		double rayEpsilon{};
	};
}

