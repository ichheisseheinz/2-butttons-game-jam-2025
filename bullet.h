#pragma once

#include "raylib.h"
#include "raymath.h"
#include "enemy.h"

namespace bullet
{
	class Bullet
	{
	private:
		Vector2 position;
		float rotation;
		int speed;
		Vector2 velocity;
	public:
		Bullet();
		Bullet(Vector2 position, float rotation);

		bool active;

		bool Update(float dt, enemy::Enemy enemies[], int numEnemies);
		void Draw();
	};
}
