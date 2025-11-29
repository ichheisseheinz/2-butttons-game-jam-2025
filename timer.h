#pragma once

#include "raylib.h"

struct Timer
{
	double startTime{ 0 };
	float totalTime{ 0 };

	void Start(float total);
	bool IsActiveTimer();
};
