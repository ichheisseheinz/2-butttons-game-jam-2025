#pragma once

#include "raylib.h"
#include "enemy.h"

namespace player
{
	class Player
	{
	private:
		Vector2 position;
		float velocity;

		int speed;
		char accelerationSpeed;

		float rotation;

		int health;
		util::Timer damageCooldown;
		bool IsTakingDamage(enemy::Enemy enemies[], int numEnemies);
	public:
		Player(Vector2 position, float rotation, int speed);

		void Update(float dt, enemy::Enemy enemies[], int numEnemies);
		void Draw();

		float GetXPosition();
		float GetRotation();
		int GetHealth();
	};
}
