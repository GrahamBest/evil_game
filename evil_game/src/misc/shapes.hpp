#pragma once

#include <SDL.h>
#include "../main.hpp"

// Draw floor
static inline void draw_floor(float x1, float y1, float x2, float y2) 
{    
    // Choose texture to draw
    glBindTexture(GL_TEXTURE_2D, main_ptr->read_textures[MAP_FLOOR]);

    // Setup texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Enable using texture
    glEnable(GL_TEXTURE_2D);

    // Setup color
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, 0.0f, y1);
    glTexCoord2f(0.0f, 64.0f);
    glVertex3f(x2, 0.0f, y1);
    glTexCoord2f(64.0f, 64.0f);
    glVertex3f(x2, 0.0f, y2);
    glTexCoord2f(64.0f, 0.0f);
    glVertex3f(x1, 0.0f, y2);
    glEnd();

    // Disable using textures
    glDisable(GL_TEXTURE_2D);
}

// Draw floor
static inline void draw_ceiling(float x1, float y1, float x2, float y2)
{
    // Choose texture to draw
    glBindTexture(GL_TEXTURE_2D, main_ptr->read_textures[MAP_CEILING]);

    // Setup texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Enable using texture
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, 1.0f, y1);
    glTexCoord2f(0.0f, 64.0f);
    glVertex3f(x2, 1.0f, y1);
    glTexCoord2f(64.0f, 64.0f);
    glVertex3f(x2, 1.0f, y2);
    glTexCoord2f(64.0f, 0.0f);
    glVertex3f(x1, 1.0f, y2);
    glEnd();

    // Disable using textures
    glDisable(GL_TEXTURE_2D);
}

// Draw single wall
static inline void draw_single_wall(float x1, float y1, float x2, float y2, std::int32_t id) 
{
    // Choose texture to draw
    glBindTexture(GL_TEXTURE_2D, main_ptr->read_textures[id]);

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
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x1, 0.0f, y1);
    glNormal3f(0, 0, 1);
    glTexCoord2f(width, 1.0f);
    glVertex3f(x2, 0.0f, y2);
    glNormal3f(0, 0, 1);
    glTexCoord2f(width, 0.0f);
    glVertex3f(x2, 1.0f, y2);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, 1.0f, y1);
    glEnd();

    // Disable using textures
    glDisable(GL_TEXTURE_2D);
}

static inline void draw_double_wall(float x, float y, std::int32_t drawingMode, std::int32_t id, const float wall_thickness = 0.50)
{
    if (drawingMode == 0) 
    {
        // Wall
        draw_single_wall(x + 0.5 - wall_thickness, y, x + 0.5 - wall_thickness, y + 1.0, id);
        draw_single_wall(x + 0.5 + wall_thickness, y, x + 0.5 + wall_thickness, y + 1.0, id);
        // Ending
        draw_single_wall(x + 0.5 - wall_thickness, y + 1.0, x + 0.5 + wall_thickness, y + 1.0, id);
        draw_single_wall(x + 0.5 - wall_thickness, y, x + 0.5 + wall_thickness, y, id);
    }
    else if (drawingMode == 1) 
    {
        // Wall
        draw_single_wall(x, y + 0.5 - wall_thickness, x + 1.0, y + 0.5 - wall_thickness, id);
        draw_single_wall(x, y + 0.5 + wall_thickness, x + 1.0, y + 0.5 + wall_thickness, id);
        // Ending
        draw_single_wall(x + 1.0, y + 0.5 - wall_thickness, x + 1.0, y + 0.5 + wall_thickness, id);
        draw_single_wall(x, y + 0.5 - wall_thickness, x, y + 0.5 + wall_thickness, id);
    }
    else if (drawingMode == 2) 
    {
        draw_single_wall(x, y + 0.5 - wall_thickness, x + 0.5 + wall_thickness, y + 0.5 - wall_thickness, id);
        draw_single_wall(x, y + 0.5 + wall_thickness, x + 0.5 - wall_thickness, y + 0.5 + wall_thickness, id);
        draw_single_wall(x + 0.5 - wall_thickness, y + 0.5 + wall_thickness, x + 0.5 - wall_thickness, y + 1.0, id);
        draw_single_wall(x + 0.5 + wall_thickness, y + 0.5 - wall_thickness, x + 0.5 + wall_thickness, y + 1.0, id);
    }
    else if (drawingMode == 3) 
    {
        draw_single_wall(x + 0.5 - wall_thickness, y + 0.5 - wall_thickness, x + 1.0, y + 0.5 - wall_thickness, id);
        draw_single_wall(x + 0.5 + wall_thickness, y + 0.5 + wall_thickness, x + 1.0, y + 0.5 + wall_thickness, id);
        draw_single_wall(x + 0.5 - wall_thickness, y + 0.5 - wall_thickness, x + 0.5 - wall_thickness, y + 1.0, id);
        draw_single_wall(x + 0.5 + wall_thickness, y + 0.5 + wall_thickness, x + 0.5 + wall_thickness, y + 1.0, id);
    }
    else if (drawingMode == 4) 
    {
        draw_single_wall(x + 0.5 + wall_thickness, y + 0.5 - wall_thickness, x + 1.0, y + 0.5 - wall_thickness, id);
        draw_single_wall(x + 0.5 - wall_thickness, y + 0.5 + wall_thickness, x + 1.0, y + 0.5 + wall_thickness, id);
        draw_single_wall(x + 0.5 - wall_thickness, y, x + 0.5 - wall_thickness, y + 0.5 + wall_thickness, id);
        draw_single_wall(x + 0.5 + wall_thickness, y, x + 0.5 + wall_thickness, y + 0.5 - wall_thickness, id);
    }
    else if (drawingMode == 5) 
    {
        draw_single_wall(x + 0.5 - wall_thickness, y, x + 0.5 - wall_thickness, y + 0.5 - wall_thickness, id);
        draw_single_wall(x + 0.5 + wall_thickness, y, x + 0.5 + wall_thickness, y + 0.5 + wall_thickness, id);
        draw_single_wall(x, y + 0.5 - wall_thickness, x + 0.5 - wall_thickness, y + 0.5 - wall_thickness, id);
        draw_single_wall(x, y + 0.5 + wall_thickness, x + 0.5 + wall_thickness, y + 0.5 + wall_thickness, id);
    }
    else if (drawingMode == 6) 
    {
        draw_single_wall(x + 0.5 + wall_thickness, y + 0.5 - wall_thickness, x + 0.5 + wall_thickness, y + 0.5 + wall_thickness, id);
        draw_single_wall(x + 0.5 - wall_thickness, y + 0.5 - wall_thickness, x + 0.5 - wall_thickness, y + 0.5 + wall_thickness, id);
        draw_single_wall(x + 0.5 - wall_thickness, y + 0.5 + wall_thickness, x + 0.5 + wall_thickness, y + 0.5 + wall_thickness, id);
        draw_single_wall(x + 0.5 - wall_thickness, y + 0.5 - wall_thickness, x + 0.5 + wall_thickness, y + 0.5 - wall_thickness, id);
    }
}