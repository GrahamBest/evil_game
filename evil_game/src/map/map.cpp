#include "map.hpp"
#include <iostream>
#include <SDL.h>
#include "../misc/vbovao.hpp"
#include "../misc/pixel_bmp.hpp"
#include "../misc/shapes.hpp"
#include "../main.hpp"
#include <vector>
#include <SDL_ttf.h>
#include "../player/ray.hpp"
#include "../misc/texture_functional.hpp"

c_map::c_map(std::string& file_name)
{
	this->file_name = file_name;
	this->width = 0;
	this->height = 0;
}

void c_map::get_map_enumerations()
{
	for (std::int32_t y = 0; y < this->height; y++)
	{
		for (std::int32_t x = 0; x < this->width; x++)
		{
			std::int32_t color = get_pixel(this->map_texture.surface, x, y);
			this->map[x][y] = MAP_FREE;

			if (color == 0xFFFFFF)
			{
				this->map[x][y] = W0;
			}
			else if (color == 0xAFAFAF)
			{
				this->map[x][y] = W1;
			}
			else if (color == 0x9B9B9B)
			{
				this->map[x][y] = W2;
			}
			else if (color == 0x878787)
			{
				this->map[x][y] = W3;
			}
			else if (color == 0x737373)
			{
				this->map[x][y] = W4;
			}
			else if (color == 0x646464)
			{
				this->map[x][y] = W5;
			}

			if (color == 0xFF0000)
			{
			//	this->map[x][y] = 2;
			}

			if (color == 0x0000FF)
			{
				main_ptr->player.position.x = x + 0.5f;
				main_ptr->player.position.z = y + 0.5f;

				if (get_pixel(this->map_texture.surface, x - 1, y) == 0xFFFF00)
				{
					main_ptr->player.camera_x = 270;
				}
				else if (get_pixel(this->map_texture.surface, x, y - 1) == 0xFFFF00)
				{
					main_ptr->player.camera_x = 0;
				}
				else if (get_pixel(this->map_texture.surface, x + 1, y) == 0xFFFF00)
				{
					main_ptr->player.camera_x = 90;
				}
				else if (get_pixel(this->map_texture.surface, x, y + 1) == 0xFFFF00)
				{
					main_ptr->player.camera_x = 180;
				}
			}

			if (color == 0x00FF00)
			{
			//	this->map[x][y] = MAP_MODES::MAP_MONSTER;
			}

			if (color == 0xFF8000)
			{
				this->map[x][y] = MAP_MODES::MAP_TEXTZONE;
			}

			if (color == 0xA349A4)
			{
				this->map[x][y] = MAP_MODES::MAP_SECRET;
			}
		}
	}
}

void c_map::get_map_data()
{
	this->map_data.open("resources/maps/map.dat", std::ios::in);
	std::string type;
	std::string equal;
	std::int32_t id = 0;

	if (this->map_data.is_open())
	{
		while (std::getline(this->map_data, type, '"') >> equal)
		{
			type.erase(type.size() - 1);
			equal.erase(equal.size() - 1);

			this->type_vector.push_back(type);
			this->equal_vector.push_back(equal);
			this->entid_vector.push_back(id);
			id++;
		}
	}
	else
	{
		std::printf("FATAL ERROR !!!\nFAILED TO OPEN MAP DATA FOR READING");
	}

	this->load_textures();

	this->map_data.close();
}

void c_map::load_textures()
{
	for (std::int32_t it = 0; it < this->equal_vector.size(); it++)
	{
		if (it >= this->equal_vector.size()) break;
		load_single_texture(MAP_FLOOR + it, read_texture(this->equal_vector[it + MAP_FLOOR])); // load each texture into W enumerations
	}
}

void c_map::load_map()
{
	this->map_texture = read_texture(this->file_name);

	if (this->map_texture.surface == nullptr)
	{
		std::printf("FATAL ERROR !!!!\nFAILED TO LOAD MAP %s\n", this->file_name.c_str());
		return;
	}

	this->width = this->map_texture.surface->w;
	this->height = this->map_texture.surface->h;
	this->map = new std::int32_t * [this->width];

	for (std::int32_t x = 0; x < this->width; x++)
	{
		this->map[x] = new std::int32_t[this->height];
	}

	this->get_map_enumerations();
	this->get_map_data();

	c_texture dude_texture = read_texture("resources/npcs/dude_orb.png");
	this->dude = c_dude(dude_texture);
	this->dude.setup(glm::vec3(64.0, 0.0, 64.0));
}

/*
 * TEST RAYS IGNORE
 */

c_ray ray_1;
bool hit_zone = false;

void c_map::render(std::uint8_t* keys)
{
	const float wall_thickness = 0.50;

	glm::vec3 ray_1_pos = glm::vec3(main_ptr->player.position.x + std::sin(main_ptr->player.camera_x * M_PI / 180.0f),
		0.0,
		main_ptr->player.position.z - std::cos(main_ptr->player.camera_x * M_PI / 180.0f));
	glm::vec3 hit_ray_1 = ray_1.cast(ray_1_pos, main_ptr->player.camera_x);

	for (std::int32_t x = 0; x < this->width; x++)
	{
		for (std::int32_t y = 0; y < this->height; y++)
		{
			if (map[x][y] == W0 ||
				map[x][y] == W1 || 
				map[x][y] == W2 ||
				map[x][y] == W3 ||
				map[x][y] == W4 ||
				map[x][y] == W5)
			{
				std::int32_t drawing_mode = 6;
				bool corners[4] = { false, false, false, false };
				std::int32_t corners_count = 0;
				std::int32_t color = get_pixel(this->map_texture.surface, x, y);
				if ((y >= 1 && map[x][y - 1] != 0) || (y <= this->height - 2 && map[x][y + 1] != 0)) drawing_mode = 0;
				if ((x >= 1 && map[x - 1][y] != 0) || (x <= this->width - 2 && map[x + 1][y] != 0)) drawing_mode = 1;
				if ((x >= 1 && map[x - 1][y] != 0) && (y <= this->width - 2 && map[x][y + 1] != 0)) { drawing_mode = 2; corners[0] = true; corners_count++; }
				if ((x <= this->width - 2 && map[x + 1][y] != 0) && (y <= this->width - 2 && map[x][y + 1] != 0)) { drawing_mode = 3; corners[1] = true; corners_count++; }
				if ((x <= this->width - 2 && map[x + 1][y] != 0) && (y >= 1 && map[x][y - 1] != 0)) { drawing_mode = 4; corners[2] = true; corners_count++; }
				if ((x >= 1 && map[x - 1][y] != 0) && (y >= 1 && map[x][y - 1] != 0)) { drawing_mode = 5; corners[3] = true; corners_count++; }
				
				if (corners_count == 0 || corners_count == 1)
				{
					if (map[x][y] == W0)
					{
						draw_double_wall(x, y, drawing_mode, W0);
					}
					else if (map[x][y] == W1)
					{
						draw_double_wall(x, y, drawing_mode, W1);
					}
					else if (map[x][y] == W2)
					{
						draw_double_wall(x, y, drawing_mode, W2);
					}
					else if (map[x][y] == W3)
					{
						draw_double_wall(x, y, drawing_mode, W3);
					}
					else if (map[x][y] == W4)
					{
						draw_double_wall(x, y, drawing_mode, W4);
					}
					else if (map[x][y] == W5)
					{
						draw_double_wall(x, y, drawing_mode, W5);
					}
				}

				else if (corners_count == 2) 
				{
					if (corners[0] && corners[3])
					{
						if (map[x][y] == W0)
						{
							draw_double_wall(x, y, 0, W0);
							// Half of the wall
							draw_single_wall(x, y + 0.5 - wall_thickness, x + 0.5, y + 0.5 - wall_thickness, W0);
							draw_single_wall(x, y + 0.5 + wall_thickness, x + 0.5, y + 0.5 + wall_thickness, W0);
							draw_single_wall(x, y + 0.5 - wall_thickness, x, y + 0.5 + wall_thickness, W0);
						}
						else if (map[x][y] == W1)
						{
							draw_double_wall(x, y, 0, W1);
							// Half of the wall
							draw_single_wall(x, y + 0.5 - wall_thickness, x + 0.5, y + 0.5 - wall_thickness, W1);
							draw_single_wall(x, y + 0.5 + wall_thickness, x + 0.5, y + 0.5 + wall_thickness, W1);
							draw_single_wall(x, y + 0.5 - wall_thickness, x, y + 0.5 + wall_thickness, W1);
						}
						else if (map[x][y] == W2)
						{
							draw_double_wall(x, y, 0, W2);
							// Half of the wall
							draw_single_wall(x, y + 0.5 - wall_thickness, x + 0.5, y + 0.5 - wall_thickness, W2);
							draw_single_wall(x, y + 0.5 + wall_thickness, x + 0.5, y + 0.5 + wall_thickness, W2);
							draw_single_wall(x, y + 0.5 - wall_thickness, x, y + 0.5 + wall_thickness, W2);
						}
						else if (map[x][y] == W3)
						{
							draw_double_wall(x, y, 0, W3);
							// Half of the wall
							draw_single_wall(x, y + 0.5 - wall_thickness, x + 0.5, y + 0.5 - wall_thickness, W3);
							draw_single_wall(x, y + 0.5 + wall_thickness, x + 0.5, y + 0.5 + wall_thickness, W3);
							draw_single_wall(x, y + 0.5 - wall_thickness, x, y + 0.5 + wall_thickness, W3);
						}
						else if (map[x][y] == W4)
						{
							draw_double_wall(x, y, 0, W4);
							// Half of the wall
							draw_single_wall(x, y + 0.5 - wall_thickness, x + 0.5, y + 0.5 - wall_thickness, W4);
							draw_single_wall(x, y + 0.5 + wall_thickness, x + 0.5, y + 0.5 + wall_thickness, W4);
							draw_single_wall(x, y + 0.5 - wall_thickness, x, y + 0.5 + wall_thickness, W4);
						}
						else if (map[x][y] == W5)
						{
							draw_double_wall(x, y, 0, W5);
							// Half of the wall
							draw_single_wall(x, y + 0.5 - wall_thickness, x + 0.5, y + 0.5 - wall_thickness, W5);
							draw_single_wall(x, y + 0.5 + wall_thickness, x + 0.5, y + 0.5 + wall_thickness, W5);
							draw_single_wall(x, y + 0.5 - wall_thickness, x, y + 0.5 + wall_thickness, W5);
						}
					}
				}
			}

			/*if (this->map[x][y] == MAP_MODES::MAP_MONSTER)
			{
				if (main_ptr->slimes[0].alive == true)
				{
					main_ptr->slimes[0].render();
				}
				else if (main_ptr->slimes[0].alive == false)
				{
					this->map[x][y] = MAP_MODES::MAP_FREE;
				}
			}*/

			if (this->map[x][y] == MAP_MODES::MAP_TEXTZONE &&
				static_cast<std::int32_t>(main_ptr->player.position.x) == x && static_cast<std::int32_t>(main_ptr->player.position.z) == y &&
				hit_zone == false)
			{
				std::printf("THIS IS THE SLIME MONSTER. HE IS A MONSTER OF DISGRACE AND HATRED. HE IS MOLDED IN THE DEPTHS OF\n" 
					"AZANINE WHERE HE WAITS TO SLUG AROUND HIS ENERGY. DESTROY HIS EVIL ENERGY. PRESS SPACE TO FIRE YOUR WEAPON\n");
				hit_zone = true;
			}

			if (this->map[x][y] == MAP_MODES::MAP_SECRET)
			{
				if ((this->map[static_cast<std::int32_t>(main_ptr->player.position.x + 1)][static_cast<std::int32_t>(main_ptr->player.position.z)]
					== this->map[x][y] || 
					this->map[static_cast<std::int32_t>(main_ptr->player.position.x)][static_cast<std::int32_t>(main_ptr->player.position.z + 1)]
					== this->map[x][y]) && keys[SDL_SCANCODE_E])
				{
					this->map[x][y] = MAP_MODES::MAP_FREE;

					std::printf("SECRET FOUND!\nTHANK YOU CARMACK FOR ALL YOUR HARDWORK AND DEDICATION.\nTHE PAIN ELEMENTAL'S EVIL NEGATIVE DIMENSIONAL BOUNDLESS ENERGY HAS BEEN PLACED ON DISPLAY IN HONOR OF YOU!\n");
				}

				draw_single_wall(x, y + 0.5 - wall_thickness - 0.3, x, y + 0.5 + wall_thickness, W0);
			}
		}
	}

	draw_floor(0, 0, this->map_texture.surface->w, this->map_texture.surface->h);
	draw_ceiling(0, 0, this->map_texture.surface->w, this->map_texture.surface->h);
	this->dude.render();
	this->secret.render();
}

void c_map::cleanup()
{
	for (std::int32_t x = 0; x < this->width; x++)
	{
		delete[] this->map[x];
	}

	delete this->map;
}