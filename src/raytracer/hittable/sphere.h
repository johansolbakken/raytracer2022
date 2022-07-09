#pragma once

#include "hittable.h"

namespace raytracer
{

	class Sphere : public Hittable
	{
	public:
		Sphere() = default;

		Sphere(point3 cen, float r, ref<Material> material);;

		~Sphere() override = default;

		bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

		bool boundingBox(float time0, float time1, Aabb& output_box) const override;

	private:
		static std::pair<float, float> getSphereUv(const point3& p);

	public:
		point3 m_center{};
		float m_radius{};
		ref<Material> m_material{};
	};

}
