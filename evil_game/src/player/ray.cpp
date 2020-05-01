#pragma once

#include "ray.hpp"
#include <GL/glew.h>
#include "../main.hpp"

glm::vec3 c_ray::cast(glm::vec3& from, float angle, bool draw)
{
    bool did_hit = false;
    float dir_iterator = 0.0f;

    while (did_hit == false)
    {
        dir_iterator += 0.2f;

        this->point_b = glm::vec3(from.x + dir_iterator * (std::sin(angle * M_PI / 180.0f)),
            0.0f,
            from.z - dir_iterator * (std::cos(angle * M_PI / 180.0f)));

        if (this->point_b.x >= 0.0f &&
            this->point_b.z >= 0.0f)
        {
            if (main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W0 || 
                main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W1 ||
                main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W2 ||
                main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W3 ||
                main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W4 ||
                main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W5)
            {did_hit = true;

                /* TEST DRAW */
                if (draw)
                {
                    glColor3f(1.0, 0.0, 0.0);
                    glBegin(GL_LINES);
                    glVertex3f(from.x,
                        0.25f,
                        from.z);
                    glVertex3f(this->point_b.x,
                        0.25f,
                        this->point_b.z);
                    glEnd();
                }

                return this->point_b;
            }
        }
        else
        {
            break;
        }
    }

    return from;
}

bool c_ray::cast_player_bullet(glm::vec3& from, bool cast_walls)
{
    bool did_hit = false;
    float dir_iterator = 0.0f;

    while (did_hit == false)
    {
        dir_iterator += 0.2f;

        this->point_b = glm::vec3(from.x + dir_iterator * std::sin(main_ptr->player.camera_x * M_PI / 180.0f),
            0.0f,
            from.z - dir_iterator * std::cos(main_ptr->player.camera_x * M_PI / 180.0f));

        if (std::round(this->point_b.x) == std::round(main_ptr->slimes[0].position.x) &&
            std::round(this->point_b.z) == std::round(main_ptr->slimes[0].position.z))
        {
            if (main_ptr->slimes[0].alive == true)
            {
                did_hit = true;
                main_ptr->slimes[0].alive = false;
                main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] = MAP_FREE;
                return true;
            }
        }
        else if (main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W0 ||
            main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W1 ||
            main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W2 ||
            main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W3 ||
            main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W4 ||
            main_ptr->map.map[static_cast<std::int32_t>(this->point_b.x)][static_cast<std::int32_t>(this->point_b.z)] == W5 &&
            cast_walls == true)
        {
            did_hit = true;
            return true;
        }
    }

    return false;
}

bool c_ray::cast_at_player(glm::vec3& pos, float angle)
{
    bool did_hit = false;
    float dir_iterator = 0.0f;

    while (did_hit == false)
    {
        dir_iterator += 0.2f;

        this->point_b = glm::vec3(pos.x + dir_iterator * (std::sin(angle * M_PI / 180.0f)),
            0.0f,
            pos.z - dir_iterator * (std::cos(angle * M_PI / 180.0f)));

        if (this->point_b == main_ptr->player.position)
        {
            did_hit = true;

            return true;
        }
    }
}