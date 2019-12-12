#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include "tools.hpp"
#include "Color.hpp"

class Texture
{
private:
    int width;
    int height;
    
    
public:
    Texture();
    Texture(const char* filename);
    ~Texture();

    Color* texture;

    void SetPixelColor(uint x,uint y,const Color &c);
    void clearBuffer();
    void uploadTexture() const;

    uint getWidth() const;
    uint getHeight() const;
    Color accessor(int x, int y);

    GLuint getTextureName() const;
    void load_PNG(const char* filename);
};


