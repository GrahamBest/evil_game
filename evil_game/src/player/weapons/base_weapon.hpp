#pragma once

#include <string>
#include <SDL.h>

class c_baseweapon
{
public:
	float damage;
	float ammo; // implement later
	std::string texture_name;
	std::int32_t x;
	std::int32_t y;
};