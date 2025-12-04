#pragma once

#include "raylib.h"

namespace util
{
	bool GetRightDown();
	bool GetLeftDown();
	bool GetRightPressed();
	bool GetLeftPressed();

	struct Timer
	{
		double startTime{ 0 };
		float totalTime{ 0 };

		void Start(float total);
		bool IsActiveTimer();
	};

	struct Stopwatch
	{
		double startTime{ 0 };

		void Start();
		float GetElapsedTime();
	};
}
