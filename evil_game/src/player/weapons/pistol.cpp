#include <iostream>
#include "pistol.hpp"
#include "../../misc/texture_functional.hpp"
#include <SDL_mixer.h>

void c_pistol::setup_sound(std::string& file_name)
{
    this->sound.wav = Mix_LoadWAV(file_name.c_str());
}

void c_pistol::shoot()
{
    /* shoot code */
    Mix_PlayChannel(-1, this->sound.wav, 0);
}

void c_pistol::init_pistol()
{
    this->texture_name = "resources/weapons/pistol.png";
	this->texture = read_texture(this->texture_name);
    load_single_texture(30, this->texture);
}

void c_pistol::render_pistol()
{       
    // Enable using texture
    glEnable(GL_TEXTURE_2D);

    // Choose texture to draw
    glBindTexture(GL_TEXTURE_2D, main_ptr->read_textures[30]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texture.surface->w, this->texture.surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->texture.surface->pixels);
    // Setup texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Setup color
    glColor4f(1.0, 1.0, 1.0, 1.0);

    // Calculate width
    float width = (4.0f - -4.0f) + (-10.0f - -1.0f);

	glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-4.0f, -3.0); // top left
    glTexCoord2f(1.0f, 0.0f);
	glVertex2f(4.0f, -3.0); // top right 
    glTexCoord2f(1.0f, 1.0f);
	glVertex2f(4.0f, -10.0f); // bottom right
    glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-4.0f, -10.0f); // bottom left
	glEnd();

    // Disable using textures
    glDisable(GL_TEXTURE_2D);
}