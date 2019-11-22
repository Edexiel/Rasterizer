#include "Texture.hpp"

#include <string.h>

Texture::Texture(unsigned int _width, unsigned int _height) : width{_width}, height{_height}
{
    pixels = new Color[_width * _height];
    clearBuffer();
    
    glGenTextures(1, &texture_name);
    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(unsigned int _width, unsigned int _height, const Color &c) : width{_width}, height{_height}
{
    glGenTextures(1, &texture_name);
    pixels = new Color[_width * _height]{c};
}

Texture::~Texture() {}

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

void Texture::applyTexture()
{
    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Color *Texture::getPixels()
{
    return pixels;
}