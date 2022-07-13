//
// Created by Johan Solbakken on 7/7/2022.
//

#include "lambertian.h"

#include "raytracer/ray.h"

#include "hittable/hit_record.h"
#include "textures/solidcolor.h"

#include "utils/orthonormalbasis.h"

namespace raytracer
{
    bool Lambertian::scatter(const Ray& r_in, const hit_record& rec, Color& alb, Ray& scattered, double& pdf) const
	{
        OrthonormalBasis uvw;
        uvw.build_from_w(rec.normal);
        auto direction = uvw.local(randomCosineDirection());

        scattered = Ray(rec.p, glm::normalize(direction), r_in.time());
        alb = m_albedo->value(rec.u, rec.v, rec.p);
        pdf = glm::dot(uvw.w(), scattered.direction()) / math::pi;
        return true;
    }

    double Lambertian::scatteringPdf(const Ray &r_in, const hit_record &rec, const Ray &scattered) const
    {
        auto cosine = glm::dot(rec.normal,glm::normalize(scattered.direction()));
        return cosine < 0 ? 0 : cosine / math::pi;
    }

	Lambertian::Lambertian(const Color& a) : m_albedo(createRef<SolidColor>(a))
	{
	}

	Lambertian::Lambertian(const ref<Texture>& a) : m_albedo(a)
	{

	}
} // raytracer
