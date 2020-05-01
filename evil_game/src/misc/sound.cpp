#include "sound.hpp"
#include <SDL_mixer.h>

c_sound::c_sound()
{
}

c_sound::c_sound(std::string name)
{
	this->audio = Mix_LoadMUS(name.c_str());
	if (!this->audio)
	{
		std::printf("FATAL ERROR !!!\nCOULDN'T OPEN %s\nAUDIO ERROR CODE %s\n", name.c_str(), Mix_GetError());
	}
}

c_sound::~c_sound()
{

}

void c_sound::use()
{
	Mix_PlayMusic(this->audio, -1);
}

void c_sound::pause()
{
	Mix_PauseMusic();
}