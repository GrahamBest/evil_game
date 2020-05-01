#include "player.hpp"
#include <SDL.h>
#include <cmath>
#include "../main.hpp"
#include <SDL_mixer.h>

void c_player::initialize()
{
	this->position = glm::vec3(2.5f, 0.0f, 2.5f);
}

void c_player::do_movement(std::uint8_t* keys, SDL_Event& evnt)
{
	this->do_fire(evnt);
	this->jump(keys); 
	// this->do_camera();

	this->register_movement(keys);
	if (this->camera_x > 360.0f) this->camera_x = 0.0f;
	if (this->camera_x < 0.0f) this->camera_x = 360.0f;
}

void c_player::do_camera()
{
	if (this->cam_left) this->camera_x -= 4.0f;
	if (this->cam_right) this->camera_x += 4.0f;
}


std::int32_t mouse_x;
void c_player::register_movement(std::uint8_t* keys)
{
	SDL_PumpEvents();
	if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])
	{
		if (main_ptr->map.map[static_cast<std::int32_t>(this->position.x + std::sin(this->camera_x * M_PI / 180.0f) - 0.05f)][static_cast<std::int32_t>(this->position.z - std::cos(this->camera_x * M_PI / 180.0f) - 0.05f)] == MAP_MODES::MAP_FREE ||
			main_ptr->map.map[static_cast<std::int32_t>(this->position.x + std::sin(this->camera_x * M_PI / 180.0f) - 0.05f)][static_cast<std::int32_t>(this->position.z - std::cos(this->camera_x * M_PI / 180.0f) - 0.05f)] == MAP_MODES::MAP_TEXTZONE) // 2 is unimplemented
		{
			this->is_moving = true;
			this->position.x += std::sin(this->camera_x * M_PI / 180.0f) * (this->velocity * this->acceleration);
			this->position.z -= std::cos(this->camera_x * M_PI / 180.0f) * (this->velocity * this->acceleration);
			this->acceleration += 0.07f;
		}
	}
	else if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN])
	{
		if (main_ptr->map.map[static_cast<std::int32_t>(this->position.x - std::sin(this->camera_x * M_PI / 180.0f) + 0.05f)][static_cast<std::int32_t>(this->position.z + std::cos(this->camera_x * M_PI / 180.0f))] == MAP_MODES::MAP_FREE ||
			main_ptr->map.map[static_cast<std::int32_t>(this->position.x - std::sin(this->camera_x * M_PI / 180.0f) + 0.05f)][static_cast<std::int32_t>(this->position.z + std::cos(this->camera_x * M_PI / 180.0f))] == MAP_MODES::MAP_TEXTZONE)
		{
			this->is_moving = true;
			this->position.x -= std::sin(this->camera_x * M_PI / 180.0f) * (this->velocity * this->acceleration);
			this->position.z += std::cos(this->camera_x * M_PI / 180.0f) * (this->velocity * this->acceleration);
			this->acceleration += 0.07f;
		}
	}
	else
	{
		this->acceleration = 0.0f;
	}

	if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
	{
		this->is_moving = true;
		this->camera_x -= 1.3f;
	}
	else if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
	{
		this->is_moving = true;
		this->camera_x += 1.3f;
	}

	if (keys[SDL_SCANCODE_LSHIFT])
	{
		if (this->acceleration > 1.8f) this->acceleration = 1.8f;
	}
	else if (this->acceleration > 1.0f) this->acceleration = 1.0f;
}

bool shoot = false;
void c_player::do_fire(SDL_Event& lmb)
{
	if (lmb.type == SDL_MOUSEBUTTONDOWN)
	{
		if (!shoot && lmb.button.button == SDL_BUTTON_LEFT)
		{
			c_ray ray;
			glm::vec3 ray_pos = glm::vec3(this->position.x,
				0.0,
				this->position.z);

			ray.cast_player_bullet(ray_pos);
			this->pistol.shoot();
			shoot = true;
		}
	}
	else 
	{
		shoot = false;
	}
}

bool down_fl = false;
void c_player::jump(std::uint8_t* keys)
{
	if (keys[SDL_SCANCODE_SPACE])
	{
		if (this->position.y < this->max_jump_val
			&& down_fl == false)
		{
			jump_punch(0.01f);
			
			if (this->position.y >= this->max_jump_val)
			{
				down_fl = true;
			}
		}
		else if (this->position.y >= 0.0f
			&& down_fl == true)
		{
			this->position.y -= 0.015f;
		
			if (this->position.y <= 0.0f)
			{
				down_fl = false;
				return;
			}
		}
	}
	else
	{
		if (this->position.y >= 0.0f)
		{
			this->position.y -= 0.015f;
			
			if (this->position.y <= 0.0f)
			{
				down_fl = false;
				return;
			}
		}
	}
}

float c_player::jump_punch(float val)
{
	if (this->position.y < this->max_jump_val)
	{
		this->position.y += val;
	}

	return this->position.y;
}