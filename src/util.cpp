#include "util.h"

using namespace util;

bool util::GetRightDown()
{
	return IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
}

bool util::GetLeftDown()
{
	return IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
}

bool util::GetRightPressed()
{
	return IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D);
}

bool util::GetLeftPressed()
{
	return IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A);
}

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