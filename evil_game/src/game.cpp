#include <iostream>
#include <cstdint>
#include "misc/texture_functional.hpp"
#include "main.hpp"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_audio.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include <SDL_ttf.h>
#include <SDL_audio.h>
#include "entities/slimey.hpp"
#include "misc/sound.hpp"

bool c_main::initialize()
{
	// intializate SDL, check for failure
	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE) < 0)
	{
		std::printf("FATAL ERROR !!!!\nSDL INITIALIZATION FAILED WITH ERROR CODE: %s\n", SDL_GetError());
		this->init_success = false;
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))
	{
		std::printf("FATAL ERROR !!!!\nSDL IMG INITIALIZATION FAILED WITH ERROR CODE : % s\n", SDL_GetError());
		this->init_success = false;
		return false;
	}

	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); 
	Mix_Init(MIX_INIT_MOD);
	Mix_Volume(-1, MIX_MAX_VOLUME);

	// set opengl version on SDL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// create the window
	this->window = SDL_CreateWindow("Evil (32-bit)",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (this->window == nullptr)
	{
		std::printf("FATAL ERROR !!!!\nWINDOW COULDN'T BE CREATED WITH ERROR CODE %s\n", SDL_GetError());
		this->init_success = false;
		return false;
	}

	this->main_renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

	if (this->main_renderer == nullptr)
	{
		std::printf("FATAL ERROR !!!!\RENDERER COULDN'T BE CREATED WITH ERROR CODE %s\n", SDL_GetError());
		this->init_success = false;
		return false;
	}

	// create opengl context
	this->context = SDL_GL_CreateContext(this->window);

	if (this->context == nullptr)
	{
		std::printf("FATAL ERROR !!!!\nOPENGL CONTEXT COULDN'T BE CREATED WITH ERROR CODE %s\n", SDL_GetError());
		this->init_success = false;
		return false;
	}

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		std::printf("FATAL ERROR !!!!\nCOULDN'T ENABLE VSYNC WITH ERROR CODE %s\n", SDL_GetError());
		this->init_success = false;
		return false;
	}

	// turn on text input
	SDL_StartTextInput();

	if (!this->initialize_opengl())
	{
		std::printf("FATAL ERROR !!!!\nCOULDN'T INITIALIZE OPENGL WITH ERROR CODE %s\n", SDL_GetError());
		this->init_success = false;
		return false;
	}

	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_WarpMouseInWindow(this->window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	
	float ambient[4] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	c_sound music = c_sound("sounds/music/e1m1_.wav");
	this->player.initialize();
	map.load_map();
	this->initialize_textures();
	this->initialize_monsters();
	Mix_VolumeMusic(MIX_MAX_VOLUME);
	std::string pistol_wav = "sounds/weapons/beretta_shot.wav";
	this->player.pistol.setup_sound(pistol_wav);
	
	// music.use

	// if succeeded
	return this->init_success;
}

void c_main::game_loop(SDL_Event& event)
{
	std::uint8_t* keystates = const_cast<std::uint8_t*>(SDL_GetKeyboardState(NULL));

	while (is_playing == true) 
	{
		if (SDL_PollEvent(&event) >= 0);
		{
			if (this->queue_quit(event) == true) this->is_playing = false;
		}

		this->player.do_movement(keystates, event);
		this->update_frame();
		this->render_scene(keystates);

		SDL_GL_SwapWindow(this->window);
	}
}

void c_main::update_frame()
{
	glViewport((WINDOW_WIDTH - WINDOW_HEIGHT) / 2, 0, WINDOW_HEIGHT, WINDOW_HEIGHT);
}

void c_main::render_scene(std::uint8_t* keystates)
{
	// clear ogl buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup the viewport
	glViewport(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// turn on matrixview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set perspective
	gluPerspective(60.0f, 1.0f * WINDOW_WIDTH / WINDOW_HEIGHT, 0.05f, 500.0f);

	glRotatef(this->player.camera_x, 0.0f, 1.0f, 0.0f);
	glPushMatrix();

	glTranslatef(-this->player.position.x, -this->player.position.y - 0.5, -this->player.position.z);

	/*
		3D RENDERING
		3D RENDERING
		3D RENDERING
	*/

	this->map.render(keystates);
	this->map.dude.think(keystates);

	glMatrixMode(GL_PROJECTION); // Tell opengl that we are doing project matrix work
	glLoadIdentity(); // Clear the matrix
	glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0); // Setup an Ortho view
	glMatrixMode(GL_MODELVIEW); // Tell opengl that we are doing model matrix work. (drawing)
	glLoadIdentity(); // Clear the model matrix
	
	/*
		2D RENDERING
		2D RENDERING
		2D RENDERING
	*/

	this->player.pistol.render_pistol();

	glPopMatrix();
	glFlush();
}

bool c_main::queue_quit(SDL_Event& event)
{
	if (event.type == SDL_QUIT) return true;
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) return true;
	return false;
}

void c_main::clean()
{
	SDL_DestroyWindow(this->window);
	this->window = nullptr;
	this->map.cleanup();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool c_main::initialize_opengl()
{
	// initialize the projection matrice
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// initialize view model matrice
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// turn on depth buffer
	glEnable(GL_DEPTH_TEST);
	// turn on normalization
	glEnable(GL_NORMALIZE);
	 

	// turn on smoothing

	glDepthRange(0.0f, 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0); 

	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glLineWidth(2.0);
	glPointSize(10.0);

	return this->init_success;
}

void c_main::initialize_textures()
{
	std::string file_name = "resources/world/textures.bmp";
	/* convert this to work with map, get hardcoded 0's fixed up */
	this->textures[RESOURCE_TEXTURES] = read_texture(file_name);
	load_single_texture(MAP_CEILING, read_texture("resources/world/e1m1/ceiling.png"));
	this->player.pistol.init_pistol();
	//this->map.secret.initialize(glm::vec3());
}

void c_main::initialize_monsters()
{
	c_slimey slime_1;
	glm::vec3 slime_position = glm::vec3(34, 0, 31);
	slime_1.initialize_monster(slime_position);
	this->slimes[0] = slime_1;
	this->map.secret.initialize(glm::vec3(64.0f, 0.0, 64.0f));
}