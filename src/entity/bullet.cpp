#include "bullet.h"
#include <iterator>

bullet::Bullet::Bullet()
	: Bullet(Vector2{0, 0}, 0, 0)
{
	this->velocity = Vector2{ 0, 0 };
	this->active = false;
}

bullet::Bullet::Bullet(Vector2 position, float rotation, int speed)
	: position(position),
	rotation(rotation),
	speed(speed),
	velocity(Vector2Rotate(Vector2{ 1, 0 }, rotation * DEG2RAD)),
	active(true),
	tex(file::GetTexture("assets/bullet.png")) 
{ }

void bullet::Bullet::Update(float dt)
{
	velocity = Vector2Scale(Vector2Normalize(velocity), speed * dt);
	position = Vector2Add(position, velocity);

	if (position.y < -10 || position.y > GetScreenHeight() + 10 || position.x < -10 || position.x > GetScreenWidth() + 10)
	{
		this->active = false;
	}
}

bool bullet::Bullet::CheckCollisions(enemy::Enemy enemies[], int numEnemies)
{
	for (int i = 0; i < numEnemies; i++)
	{
		enemy::Enemy& e = enemies[i];
		if (e.active && CheckCollisionCircles(this->position, 3, e.GetPosition(), (float)e.GetSize()))
		{
			this->active = false;
			e.active = false;
			file::Play("assets/explosion.ogg");
			return true;
		}
	}

	return false;
}

void bullet::Bullet::Draw()
{
	Rectangle sourceRect = Rectangle{ 0, 0, 3, 5 };
	Rectangle destRect = Rectangle{ this->position.x, this->position.y, 6, 10 };
	DrawTexturePro(this->tex, sourceRect, destRect, Vector2{destRect.width / 2, destRect.height / 2}, this->rotation + 90, WHITE);
}
