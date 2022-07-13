//
// Created by Johan Solbakken on 7/12/2022.
//

#include "isotropic.h"

#include "raytracer/ray.h"

#include "hittable/hit_record.h"

#include "textures/texture.h"
#include "textures/solidcolor.h"

namespace raytracer
{
	Isotropic::Isotropic(Color c) : m_albedo(createRef<SolidColor>(c)) {}

	Isotropic::Isotropic(ref<Texture> a) : m_albedo(std::move(a)) {}

    bool Isotropic::scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered, double& pdf) const
	{
		scattered = Ray(rec.p, randomInUnitSpace(), r_in.time());
		attenuation = m_albedo->value(rec.u, rec.v, rec.p);
		return true;
	}
} // raytracer
