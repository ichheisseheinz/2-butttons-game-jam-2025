#include "player.h"
#include "util.h"

using namespace player;

Player::Player(float position)
	: position(position), velocity(0), speed(50), accelerationSpeed(15), rotation(-90) { }

void Player::Update(float dt)
{
	// Change velocity
	this->velocity += (int)(util::GetRightDown() - util::GetLeftDown()) * accelerationSpeed * dt;
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
}

void Player::Draw()
{
	DrawPolyLines({ this->position, (float)GetScreenHeight() - 100}, 3, 20, this->rotation, WHITE);
}

float Player::GetPosition()
{
	return this->position;
}

float Player::GetRotation()
{
	return this->rotation;
}
