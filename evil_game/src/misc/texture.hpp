#pragma once

#include <SDL.h>
#include <iostream>
#include <string>
#include <SDL_image.h>

class c_texture
{
public:
    c_texture() 
    {
        this->surface = nullptr; 
        this->file_name = "";
    }

    c_texture(std::string file_name) 
    {
        this->surface = nullptr;
        this->file_name = file_name;
    }

    c_texture(std::string file_name, SDL_Surface* surface)
    {
        this->surface = surface;
        this->file_name = file_name;
    }

    SDL_Surface* surface;
    std::string file_name;
};