#pragma once

#include <utility>

#include "hittable.h"

namespace raytracer
{
	class Material;
	class Texture;
	class Isotropic;

	class ConstantMedium : public Hittable
	{
	public:
		ConstantMedium(ref<Hittable> b, double d, ref<Texture> a);

		ConstantMedium(ref<Hittable> b, double d, Color c);

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		bool boundingBox(double time0, double time1, Aabb& output_box) const override;

	public:
		ref<Hittable> m_boundary;
		ref<Material> m_phaseFunction;
		double m_negInvDensity;
	};

} // raytracer
