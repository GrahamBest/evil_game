#pragma once

#include <SDL_mixer.h>
#include <string>
#include <cstdint>

class c_sound
{
public:
	c_sound();
	c_sound(std::string name);
	~c_sound();
	void use();
	void pause();
	Mix_Music* audio;
	Mix_Chunk* wav;
};