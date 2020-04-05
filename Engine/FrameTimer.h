#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float FrameDur();
private:
	std::chrono::steady_clock::time_point cur;
};