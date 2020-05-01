#pragma once

#include <glm/glm.hpp>
#include <cstdint>

class c_ray
{
public:
    c_ray() {};
    glm::vec3 cast(glm::vec3& from, float angle, bool draw = true);
    bool cast_player_bullet(glm::vec3& from, bool cast_walls = true);
    bool cast_at_player(glm::vec3& pos, float angle);
	glm::vec3 point_b;
};