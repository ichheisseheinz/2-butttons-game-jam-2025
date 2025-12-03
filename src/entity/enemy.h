#pragma once

#include "raylib.h"
#include "../util.h"
#include "../file/sounds.h"

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

		util::Stopwatch timeSinceActive;
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
