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

		[[nodiscard]] double noise(const point3& p) const;

	private:
		static int* perlin_generate_perm();

		static void permute(int* p, int n);

		static double trilinear_interp(double c[2][2][2], double u, double v, double w);

		static double perlin_interp(vec3 c[2][2][2], double u, double v, double w);

	private:
		static const int m_pointCount = 256;
		vec3* m_ranvec;
		int* m_permX;
		int* m_permY;
		int* m_permZ;
	};

} // raytracer

