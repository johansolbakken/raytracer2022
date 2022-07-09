#pragma once

#include <random>

namespace raytracer
{
	inline float infinity = std::numeric_limits<float>::infinity();

	inline float randomfloat()
	{
		static std::uniform_real_distribution<float> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}

	inline float randomfloat(float min, float max)
	{
		// Returns a random real in [min,max).
		return min + (max - min) * randomfloat();
	}

	template<typename T>
	inline T clamp(T x, T min, T max)
	{
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	inline int randomInt(int min, int max)
	{
		// Returns a random integer in [min,max].
		return static_cast<int>(randomfloat(min, max + 1));
	}

}
