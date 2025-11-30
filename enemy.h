#pragma once

#include "raylib.h"
#include "timer.h"

namespace enemy
{
	class Enemy
	{
	private:
		Vector2 position;
		Vector2 finalPosition;
		float rotation;
		float speed;
		int size;

		bool entering;
		timer::Stopwatch timeSinceEntered;
	public:
		Enemy();
		Enemy(Vector2 position, float speed);

		bool active;

		void Update(float dt);
		void Draw();

		Vector2 GetPosition();
		int GetSize();
	};
}
