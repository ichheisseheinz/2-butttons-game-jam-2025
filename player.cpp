#include "player.h"

using namespace player;

Player::Player(float position)
	: position(position), velocity(0), speed(50), accelerationSpeed(15), rotation(-90), canShoot(true), canSpawn(true) { }

bool player::GetRightDown()
{
	return IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
}

bool player::GetLeftDown()
{
	return IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
}

void Player::Update(float dt)
{
	// Change velocity
	this->velocity += (int)(GetRightDown() - GetLeftDown()) * accelerationSpeed * dt;
	this->velocity *= 0.95f; // Dampening

	// Clamp velocity to max
	if (this->velocity > speed)
	{
		this->velocity = speed;
	}
	else if (this->velocity < -speed)
	{
		this->velocity = -speed;
	}

	// Update position
	this->position += this->velocity;

	// Clamp position
	if (this->position < 0)
	{
		this->position = 0;
		this->velocity = 0;
	}
	else if (this->position > GetScreenWidth())
	{
		this->position = GetScreenWidth();
		this->velocity = 0;
	}

	// Update rotation
	this->rotation = this->velocity - 90;

	// Check for shooting
	if (GetRightDown() && GetLeftDown() && !this->shootCooldown.IsActiveTimer()) Shoot();

	// Spawn enemies
	if (!this->spawnCooldown.IsActiveTimer()) Spawn();

	// Update bullets
	for (int i = 0; i < maxBullets; i++)
	{
		if (this->bullets[i].active)
		{
			if (this->bullets[i].Update(dt, this->enemies, currentEnemies)) currentEnemies++;
		}
	}

	// Update enemies
	if (maxEnemies < currentEnemies)
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
}

void Player::Shoot()
{
	for (int i = 0; i < maxBullets; i++)
	{
		if (!this->bullets[i].active)
		{
			bullets[i] = bullet::Bullet::Bullet(Vector2{ this->position, (float)GetScreenHeight() - 100 }, this->rotation);
			this->shootCooldown.Start(0.2f);
			break;
		}
	}
}

void Player::Spawn()
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

void Player::Draw()
{
	DrawPolyLines({ this->position, (float)GetScreenHeight() - 100}, 3, 20, this->rotation, WHITE);

	// Draw bullets
	for (int i = 0; i < maxBullets; i++)
	{
		if (this->bullets[i].active)
		{
			this->bullets[i].Draw();
		}
	}

	// Draw Enemies
	for (int i = 0; i < maxEnemies; i++)
	{
		if (this->enemies[i].active)
		{
			this->enemies[i].Draw();
		}
	}
}
