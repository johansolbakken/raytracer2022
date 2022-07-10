#pragma once

#include <cstdint>
#include <vector>
#include "raytracer/base.h"

namespace raytracer
{
	class Aabb;
	class Ray;
	struct Intersection;

	class Primitive
	{
	public:
		Primitive();

	public:
		// Interface
		virtual Aabb worldBound() const = 0;
		[[nodiscard]] virtual bool canIntersect() const;
		virtual bool intersect(const Ray& r, Intersection* in) const = 0;
		virtual bool intersectP(const Ray& r) const = 0;
		virtual void refine(std::vector<ref<Primitive>>& refined) const;
		void fullyRefine(std::vector<ref<Primitive>>& refined) const;

		[[nodiscard]] uint32_t id() const
		{
			return m_primitiveId;
		}

	private:
		const uint32_t m_primitiveId;
		static uint32_t s_nextId;
	};


}