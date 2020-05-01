#pragma once

#include <GL/glew.h>
#include "texture.hpp"
#include <memory>
#include "../main.hpp"

static inline c_texture read_texture(std::string file_name)
{
    c_texture texture;
    texture.surface = IMG_Load(file_name.c_str());

    if (texture.surface == nullptr)
    {
        std::printf("FATAL ERROR !!!!\nTEXTURE %s COULDN'T BE LOADED FROM IMG!\n", file_name.c_str());
        return texture;
    }

    return texture;
}

static inline c_texture trim_texture(SDL_Surface* texture, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height)
{
    c_texture new_texture;
    new_texture.surface = SDL_CreateRGBSurface(texture->flags,
        width,
        height,
        texture->format->BitsPerPixel,
        texture->format->Rmask,
        texture->format->Gmask,
        texture->format->Bmask,
        texture->format->Amask);
    SDL_Rect rect = { x, y, width, height };
    SDL_BlitSurface(texture, &rect, new_texture.surface, 0);
    return new_texture;
}

static inline void load_single_texture(std::int32_t id, c_texture texture)
{
    // Prepare space gen texture and get it going
    glGenTextures(1, &main_ptr->read_textures[id]);
    glBindTexture(GL_TEXTURE_2D, main_ptr->read_textures[id]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.surface->w, texture.surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.surface->pixels);
}