#include "hit_record.h"

#include "raytracer/ray.h"

namespace raytracer
{

	void hit_record::setFaceNormal(const Ray& r, const vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
}