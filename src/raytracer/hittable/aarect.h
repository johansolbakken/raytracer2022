#pragma once

#include <utility>

#include "hittable.h"

namespace raytracer
{

	class xy_rect : public Hittable
	{
	public:
		xy_rect() = default;

		xy_rect(float _x0, float _x1, float _y0, float _y1, float _k,
				ref<Material> mat);;

		bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

		bool boundingBox(float time0, float time1, Aabb& output_box) const override;

	public:
		ref<Material> mp;
		float x0{}, x1{}, y0{}, y1{}, k{};
	};

	class xz_rect : public Hittable
	{
	public:
		xz_rect() = default;

		xz_rect(float _x0, float _x1, float _z0, float _z1, float _k,
				const ref<Material>& mat);;

		bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

		bool boundingBox(float time0, float time1, Aabb& output_box) const override;

	public:
		ref<Material> mp;
		float x0{}, x1{}, z0{}, z1{}, k{};
	};

	class yz_rect : public Hittable
	{
	public:
		yz_rect() = default;

		yz_rect(float _y0, float _y1, float _z0, float _z1, float _k,
				const ref<Material>& mat);

		bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

		bool boundingBox(float time0, float time1, Aabb& output_box) const override;

	public:
		ref<Material> mp;
		float y0{}, y1{}, z0{}, z1{}, k{};
	};

}
