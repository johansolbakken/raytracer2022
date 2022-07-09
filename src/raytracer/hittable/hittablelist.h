//
// Created by Johan Solbakken on 7/7/2022.
//

#ifndef RAY_HITTABLELIST_H
#define RAY_HITTABLELIST_H

#include "raytracer/base.h"

#include "hittable/hittable.h"

#include <utility>
#include <vector>

namespace raytracer
{

	class HittableList : public Hittable
	{
	public:
		HittableList() = default;

		explicit HittableList(const ref<Hittable>& object);

		~HittableList() override = default;

		void clear();

		void add(const ref<Hittable>& object);

		template<typename T, typename ... Args>
		void add(Args ... args)
		{
			add(createRef<T>(std::forward<Args>(args)...));
		}

		bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

		bool boundingBox(float time0, float time1, Aabb& output_box) const override;

		[[nodiscard]] std::vector<ref<Hittable>> objects() const
		{
			return m_objects;
		}

	private:
		std::vector<ref<Hittable>> m_objects;
	};

}


#endif //RAY_HITTABLELIST_H
