#include "dude.hpp"
#include "../main.hpp"
#include <SDL.h>
#include "../misc/texture_functional.hpp"

c_dude::c_dude() {  }

c_dude::c_dude(c_texture& mdl)
{
    this->dude_texture = mdl;
}

void c_dude::setup(glm::vec3 pos)
{
	this->current_state = NOTHING;
	this->position = pos;
    load_single_texture(30, this->dude_texture);
	return;
}

void c_dude::render()
{
    // Choose texture to draw
    glBindTexture(GL_TEXTURE_2D, main_ptr->read_textures[30]);

    // Setup texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->dude_texture.surface->w, this->dude_texture.surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->dude_texture.surface->pixels);

    // Enable using texture
    glEnable(GL_TEXTURE_2D);

    // Setup color

    glTranslatef(this->position.x, 0.0f, this->position.z);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0, 0.0f, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.0, 0.75f, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0, 0.75f, 0.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0, 0.0f, 0.0);
    glEnd();

    // Disable using textures
    glDisable(GL_TEXTURE_2D);
}

void c_dude::open_dialogue()
{
    // do something later
}

void c_dude::think(std::uint8_t* keys)
{
    if (keys[SDL_SCANCODE_E] && this->just_checked == false)
    {
        if (static_cast<std::int32_t>(this->position.x) == static_cast<std::int32_t>(main_ptr->player.position.x) ||
            static_cast<std::int32_t>(this->position.z) == static_cast<std::int32_t>(main_ptr->player.position.z))
		{
			this->current_state = DUDESTATES::INTERACTING;

			if (this->current_state == DUDESTATES::INTERACTING)
			{
				std::printf("Hi! I'm DUDE! You have killed approximately %i monsters!\n", 0);
                this->just_checked = true;
				return;
			}
		}
	}
}