#pragma once

#include "raytracer/base.h"

#include "utils/glmutils.h"

namespace raytracer
{
	class Ray;

	class Material;

	struct hit_record
	{
		Point3 p;
		Vector3 normal;
		float t;
		bool front_face;
		ref<Material> mat_ptr;
		float u, v;

		void setFaceNormal(const Ray& r, const Vector3& outward_normal);

	};
}
