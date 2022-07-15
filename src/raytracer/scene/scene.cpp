#include "scene/scene.h"

#include "primitives/primitive.h"
#include "lights/light.h"

namespace raytracer
{
	Scene::Scene(const ref<Primitive>& aggregate, const std::vector<ref<Light>>& lights)
		: m_aggregate(aggregate), m_lights(lights)
	{
		m_worldBound = m_aggregate->worldBound();
	}
}
