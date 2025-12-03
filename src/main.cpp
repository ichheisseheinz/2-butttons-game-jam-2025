/*
I'm sorry in advance
Don't dig deeper into the code I beg of you
*/

#include "game.h"

int main()
{
	InitWindow(game::screenWidth, game::screenHeight, "2 Buttons Game Jam");
	InitAudioDevice();
	SetTargetFPS(60);

	// Get window icon
	Image icon = LoadImage("assets/icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

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

	sounds::UnloadSounds();

	CloseAudioDevice();
	CloseWindow();

	return 0;
}
