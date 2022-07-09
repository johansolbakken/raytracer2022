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

	class Shape
	{
	public:
		Shape(const ref<Transform>& o2w, const ref<Transform>& w2o, bool ro);

		// Interface
	public:
		virtual Aabb objectBound() const = 0;

		virtual Aabb worldBound() const;

		virtual bool canIntersect() const;

		virtual void refine(std::vector<ref<Shape>>& refinement) const;

		virtual bool intersect(const Ray& ray, hit_record* rec) const;

		virtual bool intersectP(const Ray& ray) const;


	public:
		const ref<Transform> objectToWorld() const
		{
			return m_objectToWorld;
		}

		const ref<Transform> worldToObject() const
		{
			return m_worldToObject;
		}

		bool reverseOrientation() const
		{
			return m_reverseOrientation;
		}

		bool transformSwapHandedness() const
		{
			return m_transformSwapHandedness;
		}

		uint32_t id() const
		{
			return m_shapeId;
		}

	private:
		const ref<Transform> m_objectToWorld, m_worldToObject;
		const bool m_reverseOrientation, m_transformSwapHandedness;

		static uint32_t s_nextId;
		uint32_t m_shapeId;
	};
}
