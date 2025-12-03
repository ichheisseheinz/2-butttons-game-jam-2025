#include "sounds.h"

using namespace sounds;

void sounds::Play(const char* path)
{
	if (!loadedSounds.count(path))
	{
		loadedSounds.insert({ path, LoadSound(path) });
	}
	PlaySound(loadedSounds[path]);
}

void sounds::UnloadSounds()
{
	for (const auto& pair : loadedSounds)
	{
		UnloadSound(pair.second);
	}
}
