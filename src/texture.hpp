#pragma once
#include <perlin.hpp>
#include <vec3.hpp>

#include <iostream>

class Texture
{
public:
    virtual color3 value(double u, double v, const point3 &pos) const = 0;
};

class SolidColor : public Texture
{
public:
    color3 color;

    SolidColor() {}
    SolidColor(color3 col) : color(col) {}
    SolidColor(double red, double green, double blue) : SolidColor(color3(red, green, blue)) {}

    virtual color3 value(double u, double v, const point3 &pos) const
    {
        return color;
    }
};

class CheckerTexture : public Texture
{
public:
    std::shared_ptr<Texture> even;
    std::shared_ptr<Texture> odd;

    CheckerTexture() {}
    CheckerTexture(std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1) : even(t0), odd(t1) {}

    virtual color3 value(double u, double v, const point3 &pos) const;
};

class NoiseTexture : public Texture
{
public:
    Perlin noise;
    int depth{7};
    double scale{1.0};

    NoiseTexture() {}
    NoiseTexture(double scale, int depth = 7) : scale(scale), depth(depth) {}

    virtual color3 value(double u, double v, const point3 &pos) const;
};

class ImageTexture : public Texture
{
public:
    const static int bytes_per_pixel = 3;

    ImageTexture() : data(nullptr), width(0), height(0), bytes_per_scanline(0) {}
    ImageTexture(const char *filename);

    ~ImageTexture()
    {
        delete data;
    }

    virtual color3 value(double u, double v, const vec3 &pos) const;

private:
    unsigned char *data;
    int width, height;
    int bytes_per_scanline;
};
