#include "player.h"

using namespace player;

Player::Player(Vector2 position, float rotation, int speed)
	: position(position), velocity(0), speed(speed), accelerationSpeed(15), rotation(rotation), health(2) { }

void Player::Update(float dt, enemy::Enemy enemies[], int numEnemies)
{
	// Change velocity
	this->velocity += (int)(util::GetRightDown() - util::GetLeftDown()) * accelerationSpeed * dt;
	this->velocity *= 0.95f; // Dampening

	// Clamp velocity to max
	if (this->velocity > this->speed)
	{
		this->velocity = this->speed;
	}
	else if (this->velocity < -this->speed)
	{
		this->velocity = -this->speed;
	}

	// Update position
	this->position.x += this->velocity;

	// Clamp position
	if (this->position.x < 0)
	{
		this->position.x = 0;
		this->velocity = 0;
	}
	else if (this->position.x > GetScreenWidth())
	{
		this->position.x = GetScreenWidth();
		this->velocity = 0;
	}

	// Update rotation
	this->rotation = this->velocity - 90;

	// Check for any damage
	if (!this->damageCooldown.IsActiveTimer())
	{
		if (IsTakingDamage(enemies, numEnemies))
		{
			health--;
		}
	}
}

bool Player::IsTakingDamage(enemy::Enemy enemies[], int numEnemies)
{
	for (int i = 0; i < numEnemies; i++)
	{
		enemy::Enemy& e = enemies[i];
		if (e.active)
		{
			if (CheckCollisionCircles(this->position, 15, e.GetPosition(), (float)e.GetSize() - 5))
			{
				this->damageCooldown.Start(1.5f);
				return true;
			}
		}
	}

	return false;
}

void Player::Draw()
{
	DrawPolyLines(this->position, 3, 20, this->rotation, Fade(WHITE, this->damageCooldown.IsActiveTimer() ? 0.5f : 1.0f));
}

float Player::GetXPosition()
{
	return this->position.x;
}

float Player::GetRotation()
{
	return this->rotation;
}

int Player::GetHealth()
{
	return this->health;
}
