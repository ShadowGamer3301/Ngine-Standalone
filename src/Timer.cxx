#include "Timer.h"

Ngine::Timer::Timer()
{
	last = std::chrono::steady_clock::now();
}

float Ngine::Timer::mark()
{
	const auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = last - old;
	return frameTime.count();
}

float Ngine::Timer::peek()
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
}
