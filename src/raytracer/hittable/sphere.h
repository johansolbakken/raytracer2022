#pragma once

#include "hittable.h"

namespace raytracer
{

	class Sphere : public Hittable
	{
	public:
		Sphere() = default;
		Sphere(point3 cen, double r, ref<Material>  material);;

		~Sphere() override = default;

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
		bool boundingBox(double time0, double time1, Aabb &output_box) const override;

	private:
		static std::pair<double, double> getSphereUv(const point3& p);

	public:
		point3 m_center{};
		double m_radius{};
		ref<Material> m_material{};
	};

}