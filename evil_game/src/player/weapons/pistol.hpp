#pragma once

#include "base_weapon.hpp"
#include "../../misc/texture.hpp"
#include "../../misc/sound.hpp"

class c_pistol : c_baseweapon
{
public:
	void init_pistol();
	void render_pistol();
	void shoot();
	void setup_sound(std::string& file_name);
	c_texture texture;
	c_sound sound;
};