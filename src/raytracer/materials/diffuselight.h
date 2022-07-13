#pragma once

#include "material.h"
#include "raytracer/base.h"


namespace raytracer
{
	class Texture;

	class DiffuseLight : public Material
	{
	public:
		explicit DiffuseLight(const ref<Texture>& a);

		explicit DiffuseLight(Color c);

		~DiffuseLight() override = default;

		bool scatter(
                const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered, double& pdf
		) const override;

        [[nodiscard]] Color emitted(const Ray& r_in, const hit_record& rec, double u, double v, const Point3& p) const override;

	public:
		ref<Texture> m_emit;
	};

} // raytracer

