#pragma once

#include "npc.hpp"
#include <cstdint>
#include "../misc/texture.hpp"

enum DUDESTATES
{
	INTERACTING = 0,
	NOTHING = 1
};

class c_dude : public c_npc
{
public:
	c_dude();
	c_dude(c_texture& mdl);
	void open_dialogue();
	void render();
	void setup(glm::vec3 pos);
	void think(std::uint8_t* keys);
	DUDESTATES current_state;
	c_texture dude_texture;
	bool just_checked = false;
private:
	float x_pos;
	float y_pos;
	float z_pos;
};