#include "timer.h"

using namespace timer;

void Timer::Start(float total)
{
	startTime = GetTime();
	totalTime = total;
}

bool Timer::IsActiveTimer()
{
	return GetTime() - startTime < totalTime;
}

void Stopwatch::Start()
{
	startTime = GetTime();
}

float Stopwatch::GetElapsedTime()
{
	return GetTime() - startTime;
}
