#include "Texture.hpp"
#include <cstring>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() : width{0}, height{0}, texture{nullptr} {}
Texture::Texture(const char *filename)
{
    if (filename != nullptr)
        load_PNG(filename);
    texture = nullptr;
}


uint Texture::getWidth() const
{
    return width;
}
uint Texture::getHeight() const
{
    return height;
}

void Texture::load_PNG(const char *filename)
{
    stbi_set_flip_vertically_on_load(true);
    int channels;
    Color* _texture = (Color *)stbi_load(filename, &width, &height, &channels, 3);

    texture = new Color[width * height];

    for (int i = 0; i < width * height; i++)
        texture[i] = _texture[i];
    
    stbi_image_free(_texture);


}

Color Texture::accessor(float v, float u)
{
    if (v > 1 || u > 1 || v < 0 || u < 0)
        return this->texture[0];
        
    v *= width;
    u *= height;

    return this->texture[(int)v + (int)u * width];
}

void Texture::free_texture(Texture& T)
{
    if (T.texture != nullptr)
    {
        delete(T.texture);
    }
}
