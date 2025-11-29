#include "timer.h"

void Timer::Start(float total)
{
	startTime = GetTime();
	totalTime = total;
}

bool Timer::IsActiveTimer()
{
	return GetTime() - startTime < totalTime;
}
