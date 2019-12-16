#pragma once

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

    Color* texture;

    void SetPixelColor(uint x,uint y,const Color &c);
    void clearBuffer();
    void uploadTexture() const;

    uint getWidth() const;
    uint getHeight() const;
    Color accessor(float v, float u);
    static void free_texture(Texture& texture);

    GLuint getTextureName() const;
    void load_PNG(const char* filename);
};


