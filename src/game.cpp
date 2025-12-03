#include "game.h"

using namespace game;

Game::Game()
	: player(Vector2{ screenWidth / 2, (float)screenHeight - 100}, -90, 50) { }

void Game::Update(float dt)
{
	// Update player
	this->player.Update(dt, this->enemies, currentEnemies);

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
			bullets[i] = bullet::Bullet::Bullet(Vector2{ this->player.GetXPosition(), (float)GetScreenHeight() - 100}, this->player.GetRotation(), 400);
			this->shootCooldown.Start(0.2f);
			sounds::Play("assets/shoot.ogg");
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
			enemies[i] = enemy::Enemy::Enemy(Vector2{ (float)GetRandomValue(20, 480), (float)GetRandomValue(50, 300) }, 90, 100);
			this->spawnCooldown.Start(0.2f);
			break;
		}
	}
}

void Game::Draw()
{
	if (this->player.GetHealth() > 0) // Play state
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

		// Draw player health
		DrawText(TextFormat("Health: %d", this->player.GetHealth()), 10, 10, 20, RAYWHITE);
	}
	else // Game over state
	{
		const char* text = "GAME OVER";
		const int fontSize = 20;
		DrawText(text, screenWidth / 2 - MeasureText(text, fontSize) / 2, screenHeight / 2 - fontSize / 2, fontSize, RAYWHITE);
	}
}
