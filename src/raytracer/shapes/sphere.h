#pragma once

#include "hittable/hittable.h"
#include "shape.h"

namespace raytracer
{

	class Sphere : public Shape, public Hittable
	{
	public:
		Sphere(Point3 cen, float r, ref<Material> material);;

		Sphere(const ref<Transform>& o2w, const ref<Transform>& w2o, bool ro, float rad, float z0, float z1, float pm);

		~Sphere() override = default;

		bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

		bool boundingBox(float time0, float time1, Aabb& output_box) const override;

		[[nodiscard]] Aabb objectBound() const override;

		bool intersect(const Ray &ray, float *tHit, float *rayEpsilon, ref<DifferentialGeometry> &dg) const override;

		bool intersectP(const Ray &ray) const override;

		float area() const override;

	private:
		static std::pair<float, float> getSphereUv(const Point3& p);

	public:
		Point3 m_center{};
		float m_radius{};
		ref<Material> m_material{};

		float m_phiMax{};
		float m_zmin{};
		float m_zmax{};
		float m_thetaMin{}, m_thetaMax{};
	};

}
