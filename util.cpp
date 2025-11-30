#include "util.h"

bool util::GetRightDown()
{
	return IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
}

bool util::GetLeftDown()
{
	return IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
}