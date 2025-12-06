#include "player.h"

using namespace player;

Player::Player()
	: position(Vector2{0,0}),
	velocity(0),
	speed(0),
	accelerationSpeed(15),
	rotation(0),
	health(100),
	tex(file::GetTexture("assets/player.png"))
{ }

Player::Player(Vector2 position, float rotation, int speed)
	: position(position),
	velocity(0),
	speed(speed),
	accelerationSpeed(15),
	rotation(rotation),
	health(1),
	tex(file::GetTexture("assets/player.png"))
{ }

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
	if (!this->damageCooldown.IsActiveTimer() && IsTakingDamage(enemies, numEnemies))
	{
		file::Play("assets/hit.ogg");
		this->health--;
	}
}

bool Player::IsTakingDamage(enemy::Enemy enemies[], int numEnemies)
{
	for (int i = 0; i < numEnemies; i++)
	{
		if (enemies[i].active && CheckCollisionCircles(this->position, 15, enemies[i].GetPosition(), (float)enemies[i].GetSize() - 5))
		{
			this->damageCooldown.Start(1.5f);
			return true;
		}
	}

	return false;
}

void Player::Draw()
{
	int currentFrame = (int)(this->frameTimer.GetElapsedTime() * 4) % 4;
	Rectangle sourceRect = Rectangle{ 16.0f * currentFrame, 0, 16, 16 };
	Rectangle destRect = Rectangle{ this->position.x, this->position.y, 64, 64 };
	DrawTexturePro(this->tex, sourceRect, destRect, Vector2{destRect.width / 2, destRect.height / 2}, this->rotation + 90, WHITE);
	//DrawCircleLinesV(this->position, 15, RED); // debug
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

util::Stopwatch Player::GetFrameTimer()
{
	return this->frameTimer;
}
