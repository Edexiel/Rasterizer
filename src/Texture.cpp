#include "Texture.hpp"

Texture::Texture(unsigned int _width,unsigned int _height,const Color& c = (Color){0,0,0})
{
    pixels = new Color[_width*_height]{c};
}

Texture::~Texture()
{
}

void Texture::SetPixelColor(unsigned int x,unsigned int y,const Color &c)
{
    pixels[x,y] = c;
}