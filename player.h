#pragma once

#include "raylib.h"
#include "timer.h"
#include "bullet.h"
#include "enemy.h"

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

		bool canShoot;
		timer::Timer shootCooldown;
		bullet::Bullet bullets[maxBullets];
		void Shoot();

		bool canSpawn;
		timer::Timer spawnCooldown;
		enemy::Enemy enemies[maxEnemies];
		void Spawn();
	public:
		Player(float position);

		void Update(float dt);
		void Draw();
	};

	bool GetRightDown();
	bool GetLeftDown();
}
