#pragma once

#include "hittable.h"
#include "utils/glmutils.h"

namespace raytracer
{
	class MovingSphere : public Hittable
	{
	public:
		MovingSphere() = default;

		MovingSphere(Point3 cen0, Point3 cen1, double _time0, double _time1, double r, const ref<Material>& m);


		~MovingSphere() override = default;

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		bool boundingBox(double time0, double time1, Aabb& output_box) const override;

		[[nodiscard]] Point3 center(double time) const;

	private:
		Point3 m_center0{}, m_center1{};
		double m_time0{}, m_time1{};
		double m_radius{};
		ref<Material> m_material;
	};

}
