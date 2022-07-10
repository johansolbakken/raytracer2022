//
// Created by Johan Solbakken on 7/8/2022.
//

#include "perlin.h"

namespace raytracer
{
	Perlin::Perlin()
	{
		m_ranvec = new Vector3[m_pointCount];
		for (int i = 0; i < m_pointCount; ++i)
		{
			m_ranvec[i] = glm::normalize(randomVec3(-1, 1));
		}

		m_permX = perlin_generate_perm();
		m_permY = perlin_generate_perm();
		m_permZ = perlin_generate_perm();
	}

	Perlin::~Perlin()
	{
		delete[] m_ranvec;
		delete[] m_permX;
		delete[] m_permY;
		delete[] m_permZ;
	}

	float Perlin::noise(const Point3& p) const
	{
		auto u = p.x - std::floor(p.x);
		auto v = p.y - std::floor(p.y);
		auto w = p.z - std::floor(p.z);

		auto i = static_cast<int>(std::floor(p.x));
		auto j = static_cast<int>(std::floor(p.y));
		auto k = static_cast<int>(std::floor(p.z));
		Vector3 c[2][2][2];

		for (int di = 0; di < 2; di++)
			for (int dj = 0; dj < 2; dj++)
				for (int dk = 0; dk < 2; dk++)
					c[di][dj][dk] = m_ranvec[
							m_permX[(i + di) & 255] ^
							m_permY[(j + dj) & 255] ^
							m_permZ[(k + dk) & 255]
					];

		return perlin_interp(c, u, v, w);
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
		for (int i = n - 1; i > 0; i--)
		{
			int target = randomInt(0, i);
			int tmp = p[i];
			p[i] = p[target];
			p[target] = tmp;
		}
	}

	float Perlin::trilinear_interp(float (* c)[2][2], float u, float v, float w)
	{
		auto accum = 0.0;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					accum += (i * u + (1 - i) * (1 - u)) *
							 (j * v + (1 - j) * (1 - v)) *
							 (k * w + (1 - k) * (1 - w)) * c[i][j][k];

		return accum;
	}

	float Perlin::perlin_interp(Vector3 (* c)[2][2], float u, float v, float w)
	{
		auto uu = u * u * (3 - 2 * u);
		auto vv = v * v * (3 - 2 * v);
		auto ww = w * w * (3 - 2 * w);
		auto accum = 0.0;

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
				{
					Vector3 weight_v(u - i, v - j, w - k);
					accum += (i * uu + (1 - i) * (1 - uu))
							 * (j * vv + (1 - j) * (1 - vv))
							 * (k * ww + (1 - k) * (1 - ww))
							 * glm::dot(c[i][j][k], weight_v);
				}

		return accum;
	}

	float Perlin::turb(const Point3& p, int depth) const
	{
		auto accum = 0.0;
		auto temp_p = p;
		auto weight = 1.0;

		for (int i = 0; i < depth; i++)
		{
			accum += weight * noise(temp_p);
			weight *= 0.5;
			temp_p *= 2;
		}

		return std::fabs(accum);
	}
} // raytracer
