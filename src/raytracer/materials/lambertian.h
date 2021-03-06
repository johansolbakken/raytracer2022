#pragma once

#include "material.h"
#include "raytracer/base.h"

namespace raytracer
{
	class Ray;

	class Texture;

	class Lambertian : public Material
	{
	public:
		explicit Lambertian(const Color& a);

		explicit Lambertian(const ref<Texture>& a);

		~Lambertian() override = default;

        bool scatter(const Ray& r_in, const hit_record& rec, Color& albedo, Ray& scattered, double& pdf) const override;

        double scatteringPdf(const Ray& r_in, const hit_record& rec, const Ray&scattered) const override;

	private:
		ref<Texture> m_albedo;
	};

} // raytracer
