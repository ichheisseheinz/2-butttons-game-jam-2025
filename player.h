#pragma once

#include "raylib.h"
#include "timer.h"
#include "bullet.h"

namespace player
{
	constexpr int maxBullets = 10;

	class Player
	{
	private:
		float position;
		float velocity;
		float acceleration;

		int speed;
		char accelerationSpeed;

		float rotation;

		bool canShoot;
		Timer shootCooldown;
		void Shoot();

		bullet::Bullet bullets[maxBullets];

	public:
		Player(float position);

		void Update(float dt);
		void Draw();
	};

	bool GetRightDown();
	bool GetLeftDown();
}
