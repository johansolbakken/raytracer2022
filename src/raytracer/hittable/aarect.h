#pragma once

#include "hittable.h"

namespace raytracer
{

	class xy_rect : public Hittable
	{
	public:
		xy_rect() = default;

		xy_rect(double _x0, double _x1, double _y0, double _y1, double _k,
				const ref<Material>& mat);;

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		bool boundingBox(double time0, double time1, Aabb& output_box) const override;

	public:
		ref<Material> mp;
		double x0{}, x1{}, y0{}, y1{}, k{};
	};

	class xz_rect : public Hittable
	{
	public:
		xz_rect() = default;

		xz_rect(double _x0, double _x1, double _z0, double _z1, double _k,
				const ref<Material>& mat);;

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		bool boundingBox(double time0, double time1, Aabb& output_box) const override;

	public:
		ref<Material> mp;
		double x0{}, x1{}, z0{}, z1{}, k{};
	};

	class yz_rect : public Hittable
	{
	public:
		yz_rect() = default;

		yz_rect(double _y0, double _y1, double _z0, double _z1, double _k,
				const ref<Material>& mat);

		bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

		bool boundingBox(double time0, double time1, Aabb& output_box) const override;

	public:
		ref<Material> mp;
		double y0{}, y1{}, z0{}, z1{}, k{};
	};

}
