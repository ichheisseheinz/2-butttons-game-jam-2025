#include "enemy.h"
#include <cmath>

using namespace enemy;

Enemy::Enemy()
	: position(Vector2{ 0, -20 }),
	horizontalCenter(0),
	rotation(90),
	speed(0),
	size(0),
	active(false),
	tex(file::GetTexture("assets/enemy.png"))
{ }

Enemy::Enemy(Vector2 position, float rotation, int speed)
	: position(Vector2{ position.x, -20 }),
	horizontalCenter(position.x),
	rotation(rotation),
	speed(speed),
	size(10),
	active(true),
	tex(file::GetTexture("assets/enemy.png"))
{ this->timeSinceActive.Start(); }

void Enemy::Update(float dt)
{
	if (this->active)
	{
		this->position.y += this->speed * dt;
		this->position.x = this->horizontalCenter + sinf(this->timeSinceActive.GetElapsedTime() * 2) * 10;

		if (this->position.y > GetScreenHeight() + 20) this->position.y = -20; // Reset vertical position for looping

		this->rotation = cosf(this->timeSinceActive.GetElapsedTime() * 2) * -10 + 90;
	}
	else
	{
		this->position = Vector2{ 0, 0 };
	}
}

void Enemy::Draw()
{
	int currentFrame = (int)(this->timeSinceActive.GetElapsedTime() * 4) % 2;
	Rectangle sourceRect = Rectangle{ 16.0f * currentFrame, 0, 16, 16 };
	Rectangle destRect = Rectangle{ this->position.x, this->position.y, 32, 32 };
	DrawTexturePro(this->tex, sourceRect, destRect, Vector2{destRect.width / 2, destRect.height / 2}, this->rotation + 90, WHITE);
}

Vector2 Enemy::GetPosition()
{
	return this->position;
}

int Enemy::GetSize()
{
	return this->size;
}
