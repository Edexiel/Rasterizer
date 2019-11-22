#pragma once

#include "glad/glad.h"
#include <GL/glu.h>

#include "Color.hpp"

class Texture
{
private:
    unsigned int width;
    unsigned int height;
    Color* pixels;
public:
    GLuint texture_name;
    Texture(unsigned int _width,unsigned int _height);
    Texture(unsigned int _width,unsigned int _height,const Color& c);
    ~Texture();
    void SetPixelColor(unsigned int x,unsigned int y,const Color &c);
    void clearBuffer();
    void applyTexture();
    Color* getPixels();

};
