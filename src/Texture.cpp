#include "Texture.hpp"

#include <string.h>
#include "math.hpp"

Texture::Texture(uint _width, uint _height) : width{_width}, height{_height}
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

Texture::~Texture() {}

void Texture::SetPixelColor(uint x, uint y, const Color &c)
{
    pixels[x + y * width] = c;
}

void Texture::clearBuffer()
{
    memset(pixels, 0x7F, width * height * sizeof(Color));
    // for (size_t i = 0; i < width *height; i++)
    //     pixels[i] = {0xFF,0x00,0x00};
}

void Texture::uploadTexture() const
{
    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureName() const
{
    return texture_name;
}

uint Texture::getWidth() const
{
    return width;
}
uint Texture::getHeight() const
{
    return height;
}

