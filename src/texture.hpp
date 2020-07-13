#pragma once
#include <perlin.hpp>
#include <vec3.hpp>

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

    virtual color3 value(double u, double v, const point3 &pos) const
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
};

class NoiseTexture : public Texture
{
public:
    Perlin noise;
    double scale{1.0};

    NoiseTexture() {}
    NoiseTexture(double scale) : scale(scale) {}

    virtual color3 value(double u, double v, const point3 &pos) const
    {
        return color3(1) * 0.5 * (1.0 + sin(scale * pos.z + 10 * noise.turb(scale * pos)));
        // return color3(1) * noise.turb(scale * pos); //* 0.5 * (1.0 + noise.scale(scale * pos));
    }
};
