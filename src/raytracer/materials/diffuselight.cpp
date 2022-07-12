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

	DiffuseLight::DiffuseLight(Color c) : m_emit(createRef<SolidColor>(c))
	{
	}

	bool DiffuseLight::scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const
	{
		return false;
	}

	Color DiffuseLight::emitted(double u, double v, const Point3& p) const
	{
		return m_emit->value(u, v, p);
	}
} // raytracer
