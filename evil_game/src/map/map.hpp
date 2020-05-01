#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <vector>
#include "../misc/pixel_bmp.hpp"
#include <map>
#include "../misc/vbovao.hpp"
#include <utility>
#include "secrets.hpp"
#include "../player/ray.hpp"
#include <fstream>
#include "../entities/dude.hpp"

#define DATA_BUFFER 1024

enum MAP_MODES
{
	MAP_FREE = 0,
	MAP_FLOOR = 0,
	W0 = 1,
	W1,
	W2,
	W3,
	W4,
	W5,
//	MAP_BOUNDARY = 1,
//	MAP_MONSTER = 3,
	MAP_TEXTZONE = 7,
	MAP_SECRET = 8,
	MAP_CEILING = 32
};

class c_map
{
public:
	c_map(std::string& file_name);
	void load_map();
	void get_map_enumerations();
	void get_map_data();
	void load_textures();
	void render(std::uint8_t* keys);
	void cleanup();

	char map_dat_buffer[DATA_BUFFER];
	c_texture map_texture;
	std::string file_name = "";
	std::ifstream map_data;
	c_secrets secret;
	std::int32_t width = 0;
	std::int32_t height = 0; 
	std::vector<std::string> type_vector;
	std::vector<std::string> equal_vector;
	std::vector<std::int32_t> entid_vector;
	std::int32_t** map = nullptr;
	std::uint32_t total_w = 0;
	std::uint32_t total_m = 0;
	c_dude dude;
private:

};