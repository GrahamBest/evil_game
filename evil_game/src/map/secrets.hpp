#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include <string>
#include "../misc/texture.hpp"

class c_secrets
{
public:
    void initialize(glm::vec3 pos);
    void render();

    c_texture texture;
	glm::vec3 position;
    std::string file_name;
private:
};

/*
static inline void draw_secret(float x1, float y1, float x2, float y2)
{    // Choose texture to draw
    glBindTexture(GL_TEXTURE_2D, main_ptr->read_textures[5]);

    // Setup texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Enable using texture
    glEnable(GL_TEXTURE_2D);

    // Setup color
    glColor4f(1.0, 1.0, 1.0, 1.0);

    // Calculate width
    float width = (x2 - x1) + (y2 - y1);

    // Draw
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x1, 0.0f, y1);
    glTexCoord2f(width, 1.0f);
    glVertex3f(x2, 0.0f, y2);
    glTexCoord2f(width, 0.0f);
    glVertex3f(x2, 1.0f, y2);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, 1.0f, y1);
    glEnd();

    // Disable using textures
    glDisable(GL_TEXTURE_2D);
}*/