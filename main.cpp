/*
I'm sorry in advance
Don't dig deeper into the code I beg of you
*/

#include "game.h"

int main()
{
	InitWindow(game::screenWidth, game::screenHeight, "2 Buttons Game Jam");
	SetTargetFPS(60);

	game::Game game;

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		game.Update(dt);

		BeginDrawing();

		ClearBackground(BLACK);
		game.Draw();

		DrawFPS(10, 35);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
