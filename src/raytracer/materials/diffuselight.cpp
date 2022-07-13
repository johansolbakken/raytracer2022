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

    bool DiffuseLight::scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered, double& pdf) const
	{
		return false;
	}

    Color DiffuseLight::emitted(const Ray& r_in, const hit_record& rec, double u, double v, const Point3& p) const
	{
        if (rec.front_face)
                return m_emit->value(u,v,p);
        return {0,0,0};
	}
} // raytracer
