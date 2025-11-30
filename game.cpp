#include "game.h"

using namespace game;

Game::Game()
	: player(screenWidth / 2) { }

void Game::Update(float dt)
{
	// Update player
	this->player.Update(dt);

	// Spawn and update enemies
	if (!this->spawnCooldown.IsActiveTimer()) Spawn();

	if (maxEnemies < currentEnemies) // limit max enemies to prevent errors
	{
		currentEnemies = maxEnemies;
	}

	for (int i = 0; i < currentEnemies; i++)
	{
		if (this->enemies[i].active)
		{
			this->enemies[i].Update(dt);
		}
	}

	// Spawn and update bullets
	if (util::GetRightDown() && util::GetLeftDown() && !this->shootCooldown.IsActiveTimer()) Shoot();

	for (int i = 0; i < maxBullets; i++)
	{
		if (this->bullets[i].active)
		{
			if (this->bullets[i].Update(dt, this->enemies, currentEnemies)) currentEnemies++;
		}
	}
}

void Game::Shoot()
{
	for (int i = 0; i < maxBullets; i++)
	{
		if (!this->bullets[i].active)
		{
			bullets[i] = bullet::Bullet::Bullet(Vector2{ this->player.GetPosition(), (float)GetScreenHeight() - 100}, this->player.GetRotation());
			this->shootCooldown.Start(0.2f);
			break;
		}
	}
}

void Game::Spawn()
{
	for (int i = 0; i < maxEnemies; i++)
	{
		if (!this->enemies[i].active)
		{
			enemies[i] = enemy::Enemy::Enemy(Vector2{ (float)GetRandomValue(20, 480), (float)GetRandomValue(50, 300) }, 100);
			this->spawnCooldown.Start(0.2f);
			break;
		}
	}
}

void Game::Draw()
{
	this->player.Draw();

	// Draw Enemies
	for (int i = 0; i < maxEnemies; i++)
	{
		if (this->enemies[i].active)
		{
			this->enemies[i].Draw();
		}
	}

	// Draw bullets
	for (int i = 0; i < maxBullets; i++)
	{
		if (this->bullets[i].active)
		{
			this->bullets[i].Draw();
		}
	}
}
