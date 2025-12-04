#pragma once

#include "raylib.h"
#include <map>

namespace file
{
	static std::map<const char*, Sound> loadedSounds;
	static std::map<const char*, Texture> loadedTextures;

	void Play(const char* path);
	Texture GetTexture(const char* path);

	void StopSounds();
	void UnloadSounds();
	void UnloadTextures();
}
