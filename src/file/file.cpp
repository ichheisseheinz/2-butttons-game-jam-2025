#include "file.h"

void file::Play(const char* path)
{
	if (!loadedSounds.count(path))
	{
		loadedSounds.insert({ path, LoadSound(path) });
	}
	PlaySound(loadedSounds[path]);
}

Texture file::GetTexture(const char* path)
{
	if (!loadedTextures.count(path))
	{
		loadedTextures.insert({ path, LoadTexture(path) });
	}
	return loadedTextures[path];
}

void file::StopSounds()
{
	for (const auto& pair : loadedSounds)
	{
		if (IsSoundPlaying(pair.second))
		{
			StopSound(pair.second);
		}
	}
}

void file::UnloadSounds()
{
	for (const auto& pair : loadedSounds)
	{
		UnloadSound(pair.second);
	}
}

void file::UnloadTextures()
{
	for (const auto& pair : loadedTextures)
	{
		UnloadTexture(pair.second);
	}
}
