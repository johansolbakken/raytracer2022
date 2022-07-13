#pragma once

#include "utils/glmutils.h"
#include "hittable/hit_record.h"

namespace raytracer
{
	class Ray;

	struct hit_record;

	class Material
	{
	public:
		virtual ~Material() = default;

        virtual bool scatter(const Ray& r_in, const hit_record& rec, Color& albedo, Ray& scattered, double& pdf) const
        {
            return false;
        }

        virtual double scatteringPdf(const Ray& r_in, const hit_record& rec, const Ray&scattered) const {
            return 0.0;
        }

        [[nodiscard]] virtual Color emitted(const Ray& r_in, const hit_record& rec, double u, double v, const Point3& p) const
        {
			return { 0, 0, 0 };
		}
	};

}
