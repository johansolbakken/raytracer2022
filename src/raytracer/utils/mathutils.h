#pragma once

#include <random>

namespace raytracer
{
	inline double infinity = std::numeric_limits<double>::infinity();

	inline double randomDouble()
	{
		static std::uniform_real_distribution<double> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}

	inline double randomDouble(double min, double max)
	{
		// Returns a random real in [min,max).
		return min + (max - min) * randomDouble();
	}

	template<typename T>
	inline T clamp(T x, T min, T max)
	{
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	inline int randomInt(int min, int max) {
		// Returns a random integer in [min,max].
		return static_cast<int>(randomDouble(min, max+1));
	}

}