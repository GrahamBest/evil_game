#pragma once

#include <string>
#include <glm/glm.hpp>
#include <SDL.h>
#include "../../misc/texture.hpp"

#define MAX_SLIMES 32

class c_slimey
{
public:
	// void load();
	void render();
	void update_monster();
	void do_fire();
	void initialize_surface();
	void clean();
	void initialize_monster(glm::vec3& position);

	std::string file_name = "resources/monsters/slimey.png";
	c_texture texture;
	bool has_rendered = false;
	bool back = false;
	std::int32_t fire_iterator = 0;
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	bool alive = true;
private:
};