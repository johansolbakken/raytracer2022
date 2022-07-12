#include "shape.h"

#include "transformations/transformation.h"
#include "accelerator/aabb.h"
#include "geometry/differentialgeometry.h"

namespace raytracer
{

	uint32_t Shape::s_nextId = 1;

	Shape::Shape(const ref<Transform>& o2w, const ref<Transform>& w2o, bool ro)
			: m_objectToWorld(o2w),
			  m_worldToObject(w2o),
			  m_reverseOrientation(ro),
			  m_transformSwapHandedness(o2w->swapsHandedness()),
			  m_shapeId(s_nextId++)
	{

	}

	Aabb Shape::worldBound() const
	{
		return (*m_objectToWorld)(objectBound());
	}

	bool Shape::canIntersect() const
	{
		return true;
	}

	void Shape::refine(std::vector<ref<Shape> >& refinement) const
	{
		assert(0 && "Unimplemented Shape::Refine() method called");
	}

	bool Shape::intersect(const Ray& ray, double* tHit, double* rayEpsilon, ref<DifferentialGeometry>& dg) const
	{
		assert(0 && "Unimplemented Shape::intersect() method called");
		return false;
	}

	bool Shape::intersectP(const Ray& ray) const
	{
		assert(0 && "Unimplemented Shape::intersectP() method called");
		return false;
	}

	void Shape::getShadingGeometry(const Transform& obj2world, const DifferentialGeometry& dg,
			ref<DifferentialGeometry>& dgShading) const
	{
		*dgShading = dg;
	}

	ref<Transform> Shape::objectToWorld() const
	{
		return m_objectToWorld;
	}

	ref<Transform> Shape::worldToObject() const
	{
		return m_worldToObject;
	}

	bool Shape::reverseOrientation() const
	{
		return m_reverseOrientation;
	}

	bool Shape::transformSwapHandedness() const
	{
		return m_transformSwapHandedness;
	}

	uint32_t Shape::id() const
	{
		return m_shapeId;
	}

	double Shape::area() const
	{
		assert(0 && "Not implemented Shape::area() called");
		return 0;
	}

}
