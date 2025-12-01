#pragma once

#include "raylib.h"
#include "timer.h"

namespace enemy
{
	class Enemy
	{
	private:
		Vector2 position;
		float horizontalCenter;
		float rotation;
		int speed;
		int size;

		timer::Stopwatch timeSinceActive;
	public:
		Enemy();
		Enemy(Vector2 position, float rotation, int speed);

		bool active;

		void Update(float dt);
		void Draw();

		Vector2 GetPosition();
		int GetSize();
	};
}
