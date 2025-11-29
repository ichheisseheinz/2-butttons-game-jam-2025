#include "enemy.h"
#include <cmath>

using namespace enemy;

Enemy::Enemy() : Enemy(Vector2{ 0,0 }, 0) {
	this->speed = 0;
	this->entering = false;

	this->active = false;
}

Enemy::Enemy(Vector2 position, float speed)
	: position(Vector2{position.x, -20}), finalPosition(position), rotation(90), speed(speed), entering(true), active(true) { }

void Enemy::Update(float dt)
{
	if (this->entering)
	{
		this->position.y += this->speed * dt;
		if (this->position.y >= this->finalPosition.y)
		{
			this->position.y = this->finalPosition.y;
			this->entering = false;
			this->timeSinceEntered.Start();
		}
	}
	else
	{
		this->position.x = this->finalPosition.x + sinf(this->timeSinceEntered.GetElapsedTime() * 2) * 10;
	}
}

void Enemy::Draw()
{
	DrawPolyLines(this->position, 3, 10, this->rotation, RED);
}
