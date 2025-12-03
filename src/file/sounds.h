#pragma once

#include "raylib.h"
#include <map>

namespace sounds
{
	static std::map<const char*, Sound> loadedSounds;

	void Play(const char* path);
	void UnloadSounds();
}
