#include <iostream>
#include <cstdint>
#include <SDL.h>
#include <memory>
#include <GL/glew.h>
#include "main.hpp"
#undef main

std::unique_ptr<c_main> main_ptr = std::make_unique<c_main>();

std::int32_t main(std::int32_t argc, char* argv[])
{
	main_ptr->initialize();
	
	SDL_Event event;
	main_ptr->game_loop(event);
	main_ptr->clean();

	return 0;
}