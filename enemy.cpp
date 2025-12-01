#include "enemy.h"
#include <cmath>

using namespace enemy;

Enemy::Enemy()
	: position(Vector2{ 0, -20 }), horizontalCenter(0), rotation(90), speed(0), size(0), active(false) { }

Enemy::Enemy(Vector2 position, float rotation, int speed)
	: position(Vector2{ position.x, -20 }), horizontalCenter(position.x), rotation(rotation), speed(speed), size(10), active(true)
{
	this->timeSinceActive.Start();
}

void Enemy::Update(float dt)
{
	this->position.y += this->speed * dt;
	this->position.x = this->horizontalCenter + sinf(this->timeSinceActive.GetElapsedTime() * 2) * 10;

	if (this->position.y > GetScreenHeight() + 20) this->position.y = -20; // Reset vertical position for looping
}

void Enemy::Draw()
{
	DrawPolyLines(this->position, 3, this->size, this->rotation, RED);
}

Vector2 Enemy::GetPosition()
{
	return this->position;
}

int Enemy::GetSize()
{
	return this->size;
}
