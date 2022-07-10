//
// Created by Johan Solbakken on 7/8/2022.
//

#ifndef RAY_BOX_H
#define RAY_BOX_H

#include "hittable.h"

// TODO: Continue https://raytracing.github.io/books/RayTracingTheNextWeek.html#motionblur

namespace raytracer
{
	class HittableList;

	class Box : public Hittable
	{
	public:
		Box() = default;

		Box(const Point3& p0, const Point3& p1, const ref<Material>& ptr);

		bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

		bool boundingBox(float time0, float time1, Aabb& output_box) const override;

	public:
		Point3 box_min{};
		Point3 box_max{};
		ref<HittableList> sides;
	};

} // raytracer

#endif //RAY_BOX_H
