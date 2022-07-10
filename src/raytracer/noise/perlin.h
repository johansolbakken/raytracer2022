#pragma once

#include "utils/mathutils.h"
#include "utils/glmutils.h"

namespace raytracer
{
	class Perlin
	{
	public:
		Perlin();

		~Perlin();

		[[nodiscard]] float noise(const Point3& p) const;

		float turb(const Point3& p, int depth = 7) const;


	private:
		static int* perlin_generate_perm();

		static void permute(int* p, int n);

		static float trilinear_interp(float c[2][2][2], float u, float v, float w);

		static float perlin_interp(Vector3 c[2][2][2], float u, float v, float w);

	private:
		static const int m_pointCount = 256;
		Vector3* m_ranvec;
		int* m_permX;
		int* m_permY;
		int* m_permZ;
	};

} // raytracer

