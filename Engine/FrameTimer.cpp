#include "FrameTimer.h"

using std::chrono::steady_clock;

FrameTimer::FrameTimer()
{
	cur = steady_clock::now();
}

float FrameTimer::FrameDur()
{
	auto old = cur;
	cur = steady_clock::now();
	std::chrono::duration<float> dur = cur - old;
	return dur.count();
}
