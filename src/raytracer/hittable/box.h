//
// Created by Johan Solbakken on 7/8/2022.
//

#ifndef RAY_BOX_H
#define RAY_BOX_H

#include "hittable.h"

namespace raytracer
{
	class HittableList;

	class Box : public Hittable
	{
	public:
		Box() = default;
		Box(const point3& p0, const point3& p1, const ref<Material>& ptr);

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		bool boundingBox(double time0, double time1, Aabb& output_box) const override;

	public:
		point3 box_min{};
		point3 box_max{};
		ref<HittableList> sides;
	};

} // raytracer

#endif //RAY_BOX_H
