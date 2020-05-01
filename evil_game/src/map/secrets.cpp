#include "secrets.hpp"
#include "../main.hpp"
#include "../misc/texture_functional.hpp"

void c_secrets::initialize(glm::vec3 pos)
{
    this->file_name = "resources/monsters/pelemental.png";
    this->texture = read_texture(this->file_name);
    load_single_texture(31, this->texture);
    this->position = pos;
}

void c_secrets::render()
{
    // Choose texture to draw
    glBindTexture(GL_TEXTURE_2D, main_ptr->read_textures[31]);

    // Setup texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texture.surface->w, this->texture.surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->texture.surface->pixels);

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