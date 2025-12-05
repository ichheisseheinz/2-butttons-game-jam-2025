#include "game.h"

using namespace game;

Game::Game()
	: player(Vector2{ screenWidth / 2, (float)screenHeight - 100}, -90, 50), gameState(MENU) { }

void Game::Update(float dt)
{
	switch (this->gameState)
	{
	case MENU:
		if (util::GetRightPressed())
		{
			file::Play("assets/menuselect.ogg");
			this->currentButton++;
		}
		this->currentButton %= 3;

		if (util::GetLeftPressed())
		{
			switch (this->currentButton)
			{
			case 0:
				this->gameState = GAME;
				break;
			case 1:
				this->gameState = CONTROLS;
				break;
			case 2:
				this->shouldClose = true;
				break;
			}

			file::Play("assets/menuselect.ogg");
		}

		break;
	case CONTROLS:
		if (util::GetRightPressed() || util::GetLeftPressed())
		{
			file::Play("assets/menuselect.ogg");
			this->gameState = MENU;
		}

		break;
	case GAME:
		if (this->player.GetHealth() > 0)
		{
			// Update player
			this->player.Update(dt, this->enemies, currentEnemies);

			// Spawn and update enemies
			if (!this->spawnCooldown.IsActiveTimer()) Spawn();

			if (maxEnemies < currentEnemies) // limit max enemies to prevent errors
			{
				currentEnemies = maxEnemies;
			}

			for (int i = 0; i < currentEnemies; i++)
			{
				if (this->enemies[i].active)
				{
					this->enemies[i].Update(dt);
				}
			}

			// Spawn and update bullets
			if (util::GetRightDown() && util::GetLeftDown() && !this->shootCooldown.IsActiveTimer()) Shoot();

			for (int i = 0; i < maxBullets; i++)
			{
				if (this->bullets[i].active)
				{
					this->bullets[i].Update(dt);
					if (this->bullets[i].CheckCollisions(this->enemies, currentEnemies))
					{
						this->score += 10;
						currentEnemies++;
					}
				}
			}
		}
		else
		{
			this->score = 0;
			this->gameState = GAME_OVER;
		}

		break;
	case GAME_OVER:
		if (util::GetRightPressed() || util::GetLeftPressed())
		{
			file::Play("assets/menuselect.ogg");
			this->gameState = MENU;
		}

		break;
	}
}

void Game::Shoot()
{
	for (int i = 0; i < maxBullets; i++)
	{
		if (!this->bullets[i].active)
		{
			bullets[i] = bullet::Bullet::Bullet(Vector2{ this->player.GetXPosition(), (float)GetScreenHeight() - 100}, this->player.GetRotation(), 400);
			this->shootCooldown.Start(0.2f);
			file::Play("assets/shoot.ogg");
			break;
		}
	}
}

void Game::Spawn()
{
	for (int i = 0; i < maxEnemies; i++)
	{
		if (!this->enemies[i].active)
		{
			enemies[i] = enemy::Enemy::Enemy(Vector2{ (float)GetRandomValue(20, 480), (float)GetRandomValue(50, 300) }, 90, 100);
			this->spawnCooldown.Start(0.2f);
			break;
		}
	}
}

void Game::Draw()
{
	const char* text;

	switch (this->gameState)
	{
	case MENU:
		text = "Untitled Stride Game";
		DrawText(text, screenWidth / 2 - MeasureText(text, 40) / 2, 100, 40, RAYWHITE);

		// Menu buttons
		text = "Play";
		DrawText(text, screenWidth / 2 - MeasureText(text, defaultFontSize) / 2, 300, defaultFontSize, RAYWHITE);

		text = "Controls";
		DrawText(text, screenWidth / 2 - MeasureText(text, defaultFontSize) / 2, 400, defaultFontSize, RAYWHITE);

		text = "Exit";
		DrawText(text, screenWidth / 2 - MeasureText(text, defaultFontSize) / 2, 500, defaultFontSize, RAYWHITE);

		// To mark current selection
		text = "*";
		DrawText(text, 150, this->currentButton * 100 + 300, defaultFontSize, RAYWHITE);

		text = "Use right key to change options and left to select";
		DrawText(text, screenWidth / 2 - MeasureText(text, 16) / 2, 710, 16, GRAY);

		text = "All sound effects from kenney.nl";
		DrawText(text, screenWidth / 2 - MeasureText(text, 16) / 2, 740, 16, GRAY);

		text = "Created by IchHeisseHeinz for 2 Buttons Game Jam 2025";
		DrawText(text, screenWidth / 2 - MeasureText(text, 16) / 2, 770, 16, GRAY);

		break;
	case CONTROLS:
		text = "Right = Right Arrow / D";
		DrawText(text, screenWidth / 2 - MeasureText(text, defaultFontSize) / 2, 200, defaultFontSize, RAYWHITE);

		text = "Left = Left Arrow / A";
		DrawText(text, screenWidth / 2 - MeasureText(text, defaultFontSize) / 2, 250, defaultFontSize, RAYWHITE);

		text = "Use left and right to move";
		DrawText(text, screenWidth / 2 - MeasureText(text, defaultFontSize) / 2, 400, defaultFontSize, RAYWHITE);

		text = "Press both at once to shoot";
		DrawText(text, screenWidth / 2 - MeasureText(text, defaultFontSize) / 2, 450, defaultFontSize, RAYWHITE);

		text = "Press left or right to return to the menu";
		DrawText(text, screenWidth / 2 - MeasureText(text, defaultFontSize) / 2, 650, defaultFontSize, RAYWHITE);

		break;
	case GAME:
		this->player.Draw();

		// Draw Enemies
		for (int i = 0; i < maxEnemies; i++)
		{
			if (this->enemies[i].active)
			{
				this->enemies[i].Draw();
			}
		}

		// Draw bullets
		for (int i = 0; i < maxBullets; i++)
		{
			if (this->bullets[i].active)
			{
				this->bullets[i].Draw();
			}
		}

		// Draw UI
		DrawText(TextFormat("Health: %d", this->player.GetHealth()), 10, 10, defaultFontSize, RAYWHITE);

		text = TextFormat("Score %d", this->score);
		DrawText(text, screenWidth - MeasureText(text, defaultFontSize) - 10, 10, defaultFontSize, RAYWHITE);

		break;
	case GAME_OVER:
		text = "GAME OVER";
		DrawText(text, screenWidth / 2 - MeasureText(text, defaultFontSize) / 2, screenHeight / 2 - defaultFontSize / 2, defaultFontSize, RAYWHITE);

		text = "Press left or right to return to the menu";
		DrawText(text, screenWidth / 2 - MeasureText(text, defaultFontSize) / 2, 500, defaultFontSize, RAYWHITE);

		break;
	}
}
