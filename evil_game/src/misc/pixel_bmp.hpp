#pragma once

#include <SDL.h>
#include <cstdint>

enum BMP_CLR_MODES
{
    COLOR_WHITE = 0xFFFFFF,
    COLOR_BLACK = 0xFF0000,
    COLOR_RED = 0xFF0000
};

static void set_pixel(SDL_Surface* surface, std::int32_t x, std::int32_t y, std::uint32_t pixel)
{
    std::uint8_t* p = reinterpret_cast<std::uint8_t*>(surface->pixels);

    p[(y * surface->w) + x] = pixel;
}

static SDL_Color get_pixel_color(SDL_Surface* surface, std::int32_t x, std::int32_t y)
{
    std::int32_t bpp = surface->format->BytesPerPixel;
    std::uint8_t* p = reinterpret_cast<std::uint8_t*>(surface->pixels) + y * surface->pitch + x * bpp;
    std::uint32_t pixel_color = reinterpret_cast<std::uint32_t>(p);

    SDL_Color col = { 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE };

    SDL_GetRGBA(pixel_color, surface->format, &col.r, &col.g, &col.b, &col.a);

    return col;
}

static std::int32_t get_pixel(SDL_Surface* surface, std::int32_t x, std::int32_t y)
{
    std::int32_t bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    std::uint8_t* p = (std::uint8_t*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
            return *p;
            break;
    case 2:
            return *(Uint16*)p;
            break;
    case 3:
           if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
           else
                return p[0] | p[1] << 8 | p[2] << 16;
        break;
    case 4:
        return *reinterpret_cast<std::uint8_t*>(p);
        break;
    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
