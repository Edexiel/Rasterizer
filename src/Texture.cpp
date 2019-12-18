#include "Texture.hpp"
#include <cstring>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() : _width{0}, _height{0}, texture{nullptr} {}
Texture::Texture(const char *filename)
{
    if (filename != nullptr)
        load_PNG(filename);
    texture = nullptr;
}

Texture::~Texture()
{
    if (texture == nullptr)
        delete[] texture;
}

// uint Texture::getWidth() const
// {
//     return _width;
// }
// uint Texture::getHeight() const
// {
//     return _height;
// }

bool Texture::load_PNG(const char *filename)
{
    stbi_set_flip_vertically_on_load(true);
    int channels;
    texture = (Color *)stbi_load(filename,&_width, &_height, &channels, 3);

    // texture = new Color[width * height];

    // for (int i = 0; i < width * height; i++)
    //     texture[i] = _texture[i];

    // memcpy(texture, _texture, width * height * sizeof(Color));

    // stbi_image_free(_texture);
    return !(texture == nullptr);
}
