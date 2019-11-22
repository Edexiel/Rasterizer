#include "Texture.hpp"

#include <string.h>

Texture::Texture(unsigned int _width, unsigned int _height, const Color &c = (Color){0, 0, 0}): width{_width},height{_height}
{
    pixels = new Color[_width * _height]{c};
}

Texture::~Texture(){}

void Texture::SetPixelColor(unsigned int x, unsigned int y, const Color &c)
{
    pixels[x + y * width] = c;
}

void Texture::clearBuffer()
{
    memset(pixels, 0x7F, width * height * sizeof(Color));

    // for (size_t i = 0; i < screen_width *screen_height; i++)
    // {
    //     buffer[i] = {0xFF,0x00,0x00};
    // }
}

Color* Texture::getPixels()
{
    return pixels;
}