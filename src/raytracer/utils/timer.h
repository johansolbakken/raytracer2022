//
//	 Adapted from Walnut (https://github.com/TheCherno/Walnut/blob/master/Walnut/src/Walnut/Timer.h)
//

#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <utility>
#include <functional>

namespace raytracer
{
	class Timer
	{
	public:
		Timer()
		{
			reset();
		}

		void reset()
		{
			m_start = std::chrono::high_resolution_clock::now();
		}

		double elapsed()
		{
			return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(
					std::chrono::high_resolution_clock::now() - m_start).count() * 0.001f * 0.001f * 0.001f;
		}

		double elapsedMillis()
		{
			return elapsed() * 1000.0f;
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	};

	struct ScopedTimerResult
	{
		std::string name;
		double time;
	};

	class ScopedTimer
	{
	public:
		using CallbackFn = std::function<void(ScopedTimerResult)>;

		explicit ScopedTimer(std::string name, CallbackFn callback)
				: m_name(std::move(name)), m_callback(std::move(callback))
		{
		}

		~ScopedTimer()
		{
			double time = m_timer.elapsedMillis();
			m_callback({ m_name, time });
		}

	private:
		std::string m_name;
		Timer m_timer;
		CallbackFn m_callback;
	};
}
