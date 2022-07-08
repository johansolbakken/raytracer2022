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

	private:
		static const int m_pointCount = 256;
		double* m_ranfloat;
		int* m_permX;
		int* m_permY;
		int* m_permZ;
	};

} // raytracer

