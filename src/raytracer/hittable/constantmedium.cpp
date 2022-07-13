#include "constantmedium.h"

#include <utility>
#include <iostream>

#include "materials/material.h"
#include "materials/isotropic.h"

#include "raytracer/ray.h"

namespace raytracer
{
	ConstantMedium::ConstantMedium(ref<Hittable> b, double d, ref<Texture> a)
			: m_boundary(std::move(b)),
              m_negInvDensity(-1.0 / d),
			  m_phaseFunction(createRef<Isotropic>(a))
	{}

	ConstantMedium::ConstantMedium(ref<Hittable> b, double d, Color c)
			: m_boundary(std::move(b)),
              m_negInvDensity(-1.0 / d),
			  m_phaseFunction(createRef<Isotropic>(c))
	{}

	bool ConstantMedium::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
	{
		// Print occasional samples when debugging. To enable, set enableDebug true.
		constexpr bool enableDebug = false;
		constexpr bool debugging = enableDebug && (randomdouble() < 0.00001f);

		hit_record rec1, rec2;

        if (!m_boundary->hit(r, -math::infinity, math::infinity, rec1))
			return false;

        if (!m_boundary->hit(r, rec1.t+0.0001, math::infinity, rec2))
			return false;

		if (debugging) std::cerr << "\nt_min=" << rec1.t << ", t_max=" << rec2.t << '\n';

		if (rec1.t < t_min) rec1.t = t_min;
		if (rec2.t > t_max) rec2.t = t_max;

		if (rec1.t >= rec2.t)
			return false;

		if (rec1.t < 0)
			rec1.t = 0;

		const auto ray_length = r.direction().length();
		const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
		const auto hit_distance = m_negInvDensity * log(randomdouble());

		if (hit_distance > distance_inside_boundary)
			return false;

		rec.t = rec1.t + hit_distance / ray_length;
		rec.p = r.at(rec.t);

		if (debugging) {
			std::cerr << "hit_distance = " <<  hit_distance << '\n'
					  << "rec.t = " <<  rec.t << '\n'
					  << "rec.p = " <<  rec.p << '\n';
		}

		rec.normal = Vector3 (1,0,0);  // arbitrary
		rec.front_face = true;     // also arbitrary
		rec.mat_ptr = m_phaseFunction;

		return true;
	}

	bool ConstantMedium::boundingBox(double time0, double time1, Aabb& output_box) const
	{
		return m_boundary->boundingBox(time0, time1, output_box);
	}


} // raytracer
