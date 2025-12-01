#pragma once

#include "player.h"
#include "bullet.h"

namespace game
{
	constexpr int screenWidth = 500;
	constexpr int screenHeight = 800;

	constexpr int maxBullets = 10;
	constexpr int maxEnemies = 30;
	static int currentEnemies = 10;

	class Game
	{
	private:
		player::Player player;

		timer::Timer shootCooldown;
		bullet::Bullet bullets[maxBullets];
		void Shoot();

		timer::Timer spawnCooldown;
		enemy::Enemy enemies[maxEnemies];
		void Spawn();
	public:
		Game();

		void Update(float dt);
		void Draw();
	};
}
