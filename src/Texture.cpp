#include "Texture.hpp"

Texture::Texture(unsigned int _width,unsigned int _height,const Color& c = (Color){0.f,0.f,0.f,1.f})
{
    pixels = new Color[_width*_height]{c};
}

Texture::~Texture()
{
}