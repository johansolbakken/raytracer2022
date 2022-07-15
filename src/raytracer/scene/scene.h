#pragma once

#include "raytracer/base.h"
#include <vector>

#include "accelerator/aabb.h"

namespace raytracer
{
	class Primitive;
	class Light;

	class Scene
	{
	public:
		// Public scene methods
		Scene(const ref<Primitive>& aggregate, const std::vector<ref<Light>>& lights);

		Aabb worldBound() const { return m_worldBound; }

		// Scene public data

	private:
		// Scene private data
		ref<Primitive> m_aggregate;
		std::vector<ref<Light>> m_lights;
		Aabb m_worldBound;
	};

}
