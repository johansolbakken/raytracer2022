#pragma once

#include <cstdint>
#include <vector>
#include "raytracer/base.h"

namespace raytracer
{
	class Aabb;

	class Transform;

	class Ray;

	struct hit_record;

	class DifferentialGeometry;

	class Shape
	{
	public:
		Shape(const ref<Transform>& o2w, const ref<Transform>& w2o, bool ro);

		// Interface
	public:
		[[nodiscard]] virtual Aabb objectBound() const = 0;

		[[nodiscard]] virtual Aabb worldBound() const;

		[[nodiscard]] virtual bool canIntersect() const;

		virtual void refine(std::vector<ref<Shape>>& refinement) const;

		virtual bool intersect(const Ray& ray, float *tHit, float *rayEpsilon, ref<DifferentialGeometry>& dg) const;

		[[nodiscard]] virtual bool intersectP(const Ray& ray) const;

		virtual void getShadingGeometry(const Transform& obj2world, const DifferentialGeometry& dg,
				ref<DifferentialGeometry>& dgShading) const;

		[[nodiscard]] virtual float area() const;

	public:
		[[nodiscard]] ref<Transform> objectToWorld() const;

		[[nodiscard]] ref<Transform> worldToObject() const;

		[[nodiscard]] bool reverseOrientation() const;

		[[nodiscard]] bool transformSwapHandedness() const;

		[[nodiscard]] uint32_t id() const;

	private:
		const ref<Transform> m_objectToWorld, m_worldToObject;
		const bool m_reverseOrientation, m_transformSwapHandedness;

		static uint32_t s_nextId;
		uint32_t m_shapeId;
	};
}
