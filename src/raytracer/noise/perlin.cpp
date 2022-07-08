//
// Created by Johan Solbakken on 7/8/2022.
//

#include "perlin.h"

namespace raytracer
{
	Perlin::Perlin()
	{
		m_ranfloat = new double[m_pointCount];
		for (int i = 0; i < m_pointCount; ++i) {
			m_ranfloat[i] = randomDouble();
		}

		m_permX = perlin_generate_perm();
		m_permY = perlin_generate_perm();
		m_permZ = perlin_generate_perm();
	}

	Perlin::~Perlin()
	{
		delete[] m_ranfloat;
		delete[] m_permX;
		delete[] m_permY;
		delete[] m_permZ;
	}

	double Perlin::noise(const point3& p) const
	{
		auto i = static_cast<int>(4*p.x) & 255;
		auto j = static_cast<int>(4*p.y) & 255;
		auto k = static_cast<int>(4*p.z) & 255;

		return m_ranfloat[m_permX[i] ^ m_permY[j] ^ m_permZ[k]];
	}

	int* Perlin::perlin_generate_perm()
	{
		auto p = new int[m_pointCount];

		for (int i = 0; i < Perlin::m_pointCount; i++)
			p[i] = i;

		permute(p, m_pointCount);

		return p;
	}

	void Perlin::permute(int* p, int n)
	{
		for (int i = n-1; i > 0; i--) {
			int target = randomInt(0, i);
			int tmp = p[i];
			p[i] = p[target];
			p[target] = tmp;
		}
	}
} // raytracer