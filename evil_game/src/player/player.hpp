#pragma once

#include <SDL.h>
#include <thread>
#include "weapons/pistol.hpp"
#include <glm/glm.hpp>
#include "ray.hpp"
#include "../misc/sound.hpp"

class c_player
{
public:
	void initialize();
	void do_movement(std::uint8_t* keys, SDL_Event& event);
	// void do_raycasting();
	void do_fire(SDL_Event& lmb);
	void jump(std::uint8_t* keys);

	float camera_x = 0.0f;
	glm::vec3 position;
	float velocity = 0.03f;
	float acceleration = 0.2f;
	c_pistol pistol;
	float jump_val = 0.01f;
	float max_jump_val = 0.4f;
	bool is_jumping = false;
	bool is_moving = false;
	c_sound jump_sound;
	bool is_mouse_moving = false;
private:
	float jump_punch(float val);
	void register_movement(std::uint8_t* keys);
	void do_camera();
	bool moving_up = false;
	bool moving_left = false;
	bool moving_right = false;
	bool moving_back = false;
	bool cam_left = false;
	bool cam_right = false;
};