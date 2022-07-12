#pragma once

#include "hittable/hittable.h"
#include "shape.h"

#define pbrt 0

namespace raytracer
{

    class Sphere :
        #if pbrt
            public Shape,
        #endif
            public Hittable
	{
	public:
		Sphere(Point3 cen, double r, ref<Material> material);;

#if pbrt
		Sphere(const ref<Transform>& o2w, const ref<Transform>& w2o, bool ro, double rad, double z0, double z1, double pm);

#endif
		~Sphere() override = default;

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		bool boundingBox(double time0, double time1, Aabb& output_box) const override;

#if pbrt
		[[nodiscard]] Aabb objectBound() const override;

		bool intersect(const Ray &ray, double *tHit, double *rayEpsilon, ref<DifferentialGeometry> &dg) const override;

		bool intersectP(const Ray &ray) const override;

		double area() const override;
#endif

	private:
		static std::pair<double, double> getSphereUv(const Point3& p);

	public:
		Point3 m_center{};
		double m_radius{};
		ref<Material> m_material{};

		double m_phiMax{};
		double m_zmin{};
		double m_zmax{};
		double m_thetaMin{}, m_thetaMax{};
	};

}
