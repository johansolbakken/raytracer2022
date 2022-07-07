#pragma once

#include "raytracer/base.h"

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray;
	class Material;

	struct hit_record
	{
		point3 p;
		vec3 normal;
		double t;
		bool front_face;
		ref<Material> mat_ptr;

		void setFaceNormal(const Ray& r, const vec3& outward_normal);

	};
}