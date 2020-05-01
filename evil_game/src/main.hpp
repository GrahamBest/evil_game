#pragma once
#include <SDL.h>
#include <cstdint>
#include <iostream>
#include <memory>
#include "misc/texture.hpp"
#include "player/player.hpp"
#include "map/map.hpp"
#include <string>
#include "entities/slimey.hpp"
#include "misc/sound.hpp"

#define RESOURCE_TEXTURES 0 
#define MAX_TEXTURES 64

constexpr std::int32_t WINDOW_WIDTH = 1024;
constexpr std::int32_t WINDOW_HEIGHT = 720;

class c_main
{
public:
	SDL_Window* window;
	SDL_GLContext context;
	bool initialize();
	bool initialize_opengl();
	void update_frame();
	void render_scene(std::uint8_t* keys);
	void game_loop(SDL_Event& event);
	void clean();
	void initialize_textures();

	c_player player = c_player();
	std::string file_name = "resources/maps/arena.bmp";
	SDL_Surface* window_surface;
	SDL_Renderer* main_renderer;
	c_map map = c_map(file_name);
	std::uint32_t read_textures[MAX_TEXTURES];
	c_texture textures[MAX_TEXTURES];
	c_slimey slimes[MAX_SLIMES];
	float gravity = 0.01f;
private:
	void initialize_monsters();
	bool queue_quit(SDL_Event& event);

	bool is_playing = true;
	bool init_success = true;
};

extern std::unique_ptr<c_main> main_ptr;