#pragma once

#include "raylib.h"
#include "raymath.h"

namespace bullet
{
	class Bullet
	{
	private:
		Vector2 position;
		float rotation;
		int speed;
		Vector2 velocity;

	public:
		Bullet();
		Bullet(Vector2 position, float rotation);

		bool active;

		void Update(float dt);
		void Draw();
	};
}
