#define STB_IMAGE_IMPLEMENTATION
#include <texture.hpp>
#include <vec3.hpp>
#include <stb_image.h>

#include <iostream>

color3 CheckerTexture::value(double u, double v, const point3 &pos) const
{
    double sines = sin(10 * pos.x) * sin(10 * pos.y) * sin(10 * pos.z);
    if (sines < 0)
    {
        return odd->value(u, v, pos);
    }
    else
    {
        return even->value(u, v, pos);
    }
}

color3 NoiseTexture::value(double u, double v, const point3 &pos) const
{
    return color3(1) * 0.5 * (1.0 + sin(scale * pos.z + 10 * noise.turb(pos, depth)));
    // return color3(1) * noise.turb(scale * pos); //* 0.5 * (1.0 + noise.scale(scale * pos));
}

ImageTexture::ImageTexture(const char *filename)
{
    int components_per_pixel = bytes_per_pixel;
    data = stbi_load(
        filename, &width, &height, &components_per_pixel, components_per_pixel);
    if (!data)
    {
        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
        width = height = 0;
    }
    bytes_per_scanline = bytes_per_pixel * width;
}

color3 ImageTexture::value(double u, double v, const vec3 &pos) const
{
    // Pink for missing textures
    if (data == nullptr)
    {
        return color3(1, 0, 1);
    }

    // Clamp texture co-ordinates to [0,1] x [1,0]
    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0); // Flip V to image co-ordinates

    int i = static_cast<int>(u * width);
    int j = static_cast<int>(v * height);

    // Co-ordinates should be less than 1.0, clamped to image size
    if (i >= width)
    {
        i = width - 1;
    }
    if (j >= height)
    {
        j = height - 1;
    }

    const double color_scale = 1.0 / 255.0;
    auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;

    return color3(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}
