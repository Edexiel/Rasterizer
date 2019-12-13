#include "Texture.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include "tools.hpp"
#include <iostream>
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() : width{0}, height{0}, texture{nullptr} {}
Texture::Texture(const char *filename)
{
    load_PNG(filename);
}
Texture::~Texture()
{
    if (texture != nullptr)
        stbi_image_free(texture);
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
    texture = (Color *)stbi_load(filename, &width, &height, &channels, 3);
}

Color Texture::accessor(float v, float u)
{
    if (v > 1 || u > 1 || v < 0 || u < 0)
        return this->texture[0];
        
    v *= width;
    u *= height;

    return this->texture[(int)v + (int)u * width];
}
