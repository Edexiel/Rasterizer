#pragma once

#include "stb_image.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include "math.hpp"
#include "Color.hpp"

class Texture
{
private:
    uint width;
    uint height;
    
    Color* pixels; //maybe do a vector -> auto screen scale
    GLuint texture_name;
public:
    Texture(uint _width,uint _height);
    ~Texture();

    void SetPixelColor(uint x,uint y,const Color &c);
    void clearBuffer();
    void uploadTexture() const;

    uint getWidth() const;
    uint getHeight() const;

    GLuint getTextureName() const;
};


char* load_PNG(const char* filename);
