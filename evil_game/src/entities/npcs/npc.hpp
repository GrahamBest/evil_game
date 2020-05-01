#pragma once

#include <glm/glm.hpp>

class c_npc
{
public:
	virtual void render(std::int32_t id) {}
	virtual void setup(glm::vec3 pos) {}
	virtual void think() {}
	glm::vec3 position;
private:
	float x_pos;
	float y_pos;
	float z_pos;
};