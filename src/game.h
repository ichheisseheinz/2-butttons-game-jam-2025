#pragma once

#include "entity/player.h"
#include "entity/bullet.h"

namespace game
{
	constexpr int screenWidth = 500;
	constexpr int screenHeight = 800;

	constexpr int maxBullets = 10;
	constexpr int maxEnemies = 30;
	static int currentEnemies = 10;

	constexpr int defaultFontSize = 20;

	enum State
	{
		MENU,
		CONTROLS,
		GAME,
		GAME_OVER
	};

	class Game
	{
	private:
		State gameState;

		// Game state members
		player::Player player;
		int score = 0;

		util::Timer shootCooldown;
		bullet::Bullet bullets[maxBullets];
		void Shoot();

		util::Timer spawnCooldown;
		enemy::Enemy enemies[maxEnemies];
		void Spawn();

		// Menu members
		int currentButton = 0;
	public:
		Game();

		bool shouldClose = false;

		void Update(float dt);
		void Draw();
	};
}
