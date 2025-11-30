#pragma once

#include "raylib.h"

namespace player
{
	constexpr int maxBullets = 50;
	constexpr int maxEnemies = 30;
	static int currentEnemies = 10;

	class Player
	{
	private:
		float position;
		float velocity;

		int speed;
		char accelerationSpeed;

		float rotation;
	public:
		Player(float position);

		void Update(float dt);
		void Draw();

		float GetPosition();
		float GetRotation();
	};
}
