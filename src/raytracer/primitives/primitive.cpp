#include <memory>
#include "primitive.h"

namespace raytracer
{
	uint32_t Primitive::s_nextId = 1;

	Primitive::Primitive()
			: m_primitiveId(s_nextId++)
	{

	}

	bool Primitive::canIntersect() const
	{
		return true;
	}

	void Primitive::fullyRefine(std::vector<ref<Primitive>>& refined) const
	{
		std::vector<ref<Primitive>> todo;
		ref<Primitive> thisRef = createRef<Primitive>(this);

		todo.push_back(thisRef);
		while (!todo.empty())
		{
			ref<Primitive> prim = todo.back();
			todo.pop_back();
			if (prim->canIntersect())
			{
				refined.push_back(prim);
			}
			else
			{
				prim->refine(todo);
			}

		}
	}
}