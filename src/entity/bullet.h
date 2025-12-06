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

		Texture tex;
	public:
		Bullet();
		Bullet(Vector2 position, float rotation, int speed);

		bool active;

		void Update(float dt);
		void Draw();
		bool CheckCollisions(enemy::Enemy enemies[], int numEnemies);
	};
}
