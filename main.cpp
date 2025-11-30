/*
I'm sorry in advance
Don't dig deeper into the code I beg of you
*/

#include "raylib.h"

#include "player.h"

int main()
{
	const int screenWidth = 500;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "2 Buttons Game Jam");
	SetTargetFPS(60);

	player::Player player(screenWidth / 2);

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		player.Update(dt);

		BeginDrawing();

		ClearBackground(BLACK);
		player.Draw();

		DrawFPS(0, 0);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
