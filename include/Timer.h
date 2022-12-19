#pragma once
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
