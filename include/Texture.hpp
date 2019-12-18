#pragma once

#include <GL/glu.h>

#include "tools.hpp"
#include "Color.hpp"

class Texture
{
private:
    int _width;
    int _height;
    Color *texture;

public:
    Texture();
    Texture(const char *filename);
    ~Texture();

    Color *getTexture() const;

    void uploadTexture() const;
    bool isEmpty() const;

    // uint getWidth() const;
    // uint getHeight() const;
    Color accessor(float v, float u) const;

    GLuint getTextureName() const;
    bool load_PNG(const char *filename);
};
inline Color *Texture::getTexture() const
{
    return texture;
}

inline bool Texture::isEmpty() const
{
    return texture == nullptr;
}

inline Color Texture::accessor(float v, float u) const
{
    if (isEmpty() || v > 1 || u > 1 || v < 0 || u < 0)
    {
        std::cout << "Error: Trying to access invalid texture with parameters : u=>" << u << " v=>" << v << std::endl;
        return {255, 0, 0};
    }

    // wtf ?
    v *= _width;
    u *= _height;

    return this->texture[(int)v + (int)u * _width];
}
