#include "bullet.h"

using namespace bullet;

Bullet::Bullet()
	: Bullet(Vector2{0, 0}, 0)
{
	this->speed = 0;
	this->velocity = Vector2{ 0, 0 };
	this->active = false;
}

Bullet::Bullet(Vector2 position, float rotation)
	: position(position), rotation(rotation), speed(400), velocity(Vector2Rotate(Vector2{ 1, 0 }, rotation * DEG2RAD)), active(true) { }

void Bullet::Update(float dt)
{
	velocity = Vector2Scale(Vector2Normalize(velocity), speed * dt);
	position = Vector2Add(position, velocity);

	if (position.y < -10 || position.x < -10 || position.x > GetScreenWidth() + 10)
	{
		this->active = false;
	}
}

void Bullet::Draw()
{
	DrawCircleV(this->position, 3, WHITE);
}
