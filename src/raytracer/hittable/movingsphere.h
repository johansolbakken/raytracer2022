#pragma once

#include "hittable.h"
#include "utils/glmutils.h"

namespace raytracer
{
	class MovingSphere : public Hittable
	{
	public:
		MovingSphere() = default;

		MovingSphere(Point3 cen0, Point3 cen1, float _time0, float _time1, float r, const ref<Material>& m);


		~MovingSphere() override = default;

		bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

		bool boundingBox(float time0, float time1, Aabb& output_box) const override;

		[[nodiscard]] Point3 center(float time) const;

	private:
		Point3 m_center0{}, m_center1{};
		float m_time0{}, m_time1{};
		float m_radius{};
		ref<Material> m_material;
	};

}
