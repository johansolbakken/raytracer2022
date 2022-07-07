#pragma once

namespace raytracer
{
	class Ray;

	struct hit_record;

	class color;

	class Material
	{
	public:
		virtual bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const = 0;
	};

}
