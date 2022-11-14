#pragma once
#include "Macro.h"

#ifdef _WIN32
#include <chrono>

namespace Ngine
{
	class NAPI Timer
	{
	public:
		Timer();

		float mark();
		float peek();

	private:
		std::chrono::steady_clock::time_point last;
	};
}
#elif defined __linux__
#include <chrono>

namespace Ngine
{
	class Timer
	{
	public:
		Timer();

		float mark();
		float peek();

	private:
		std::chrono::steady_clock::time_point last;
	};
}

#endif