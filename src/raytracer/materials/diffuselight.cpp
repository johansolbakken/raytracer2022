//
// Created by Johan Solbakken on 7/8/2022.
//

#include "diffuselight.h"

#include "textures/solidcolor.h"

namespace raytracer
{
	DiffuseLight::DiffuseLight(const ref<Texture>& a) : m_emit(a)
	{
	}

	DiffuseLight::DiffuseLight(color c) : m_emit(createRef<SolidColor>(c))
	{
	}

	bool DiffuseLight::scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const
	{
		return false;
	}

	color DiffuseLight::emitted(float u, float v, const point3& p) const
	{
		return m_emit->value(u, v, p);
	}
} // raytracer
