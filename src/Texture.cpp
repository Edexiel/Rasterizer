#include "Texture.hpp"
<<<<<<< HEAD

#include <string.h>
#include "tools.hpp"

Texture::Texture(uint _width, uint _height) : width{_width}, height{_height}
=======
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
>>>>>>> 5d5d64de5cb364cf01135f08b8f6c441a603f3a5
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

Color Texture::accessor(int x, int y)
{
    return this->texture[x + y * width];
}
