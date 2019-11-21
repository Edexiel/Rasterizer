#pragma once

#include "Color.hpp"

class Texture
{
private:
    unsigned int width;
    unsigned int height;
    Color* pixels;
public:
    Texture(unsigned int _width,unsigned int _height,const Color& c);
    ~Texture();
    void SetPixelColor(unsigned int x,unsigned int y,const Color &c);
};
