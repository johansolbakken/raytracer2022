#pragma once

#include <random>

namespace raytracer
{
namespace math {
    constexpr double pi = 3.14159265358979323846;

	inline double infinity = std::numeric_limits<double>::infinity();
}
	inline double randomdouble()
	{
		static std::uniform_real_distribution<double> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}

	// todo: rename to randomdouble
	inline double randomdouble(double min, double max)
	{
		// Returns a random real in [min,max).
		return min + (max - min) * randomdouble();
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
		return static_cast<int>(randomdouble(min, max + 1));
	}

	inline bool equalsDouble(double a, double b) {
		return std::abs(a - b) < std::numeric_limits<double>::epsilon();
	}

}
