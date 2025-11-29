#include "player.h"

using namespace player;
using namespace bullet;

Player::Player(float position)
{
	this->position = position;
	this->velocity = 0;

	this->speed = 50;
	this->accelerationSpeed = 15;

	this->rotation = -90; // Facing up

	this->canShoot = true;
}

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
	this->velocity *= 0.95f; // Friction/dampening

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
	if (GetRightDown() && GetLeftDown())
	{
		Shoot();
	}

	// Update bullets
	for (int i = maxBullets - 1; i >= 0; --i)
	{
		if (this->bullets[i].active)
		{
			this->bullets[i].Update(dt);
		}
	}

	// Update timers
	this->canShoot = !this->shootCooldown.IsActiveTimer();
}

void Player::Shoot()
{
	if (this->canShoot)
	{
		for (int i = 0; i < maxBullets; i++)
		{
			if (this->bullets[i].active) continue;

			bullets[i] = Bullet::Bullet(Vector2{ this->position, (float)GetScreenHeight() - 100 }, this->rotation);
			break;
		}
		this->shootCooldown.Start(0.2f);
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
}
