#pragma once
#include <cmath>
#include <iostream>
#include <utils.hpp>

class vec3
{
public:
    union
    {
        double data[3];
        struct
        {
            double x;
            double y;
            double z;
        };
        struct
        {
            double r;
            double g;
            double b;
        };
    };

    vec3() : data{0, 0, 0} {}
    vec3(double x) : data{x, x, x} {}
    vec3(double x, double y, double z) : data{x, y, z} {}

    vec3 operator-() const { return vec3(-x, -y, -z); }
    double operator[](int i) const { return data[i]; }
    double &operator[](int i) { return data[i]; }

    vec3 &operator+=(const vec3 &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    vec3 &operator*=(const double t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    vec3 &operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    inline static vec3 random()
    {
        return vec3(randDouble(), randDouble(), randDouble());
    }

    inline static vec3 random(double min, double max)
    {
        return vec3(randDouble(min, max), randDouble(min, max), randDouble(min, max));
    }
};

using point3 = vec3;
using color3 = vec3;

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec3 operator+(const vec3 &lhs, const vec3 &rhs)
{
    return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline vec3 operator-(const vec3 &lhs, const vec3 &rhs)
{
    return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline vec3 operator*(const vec3 &lhs, const vec3 &rhs)
{
    return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

inline vec3 operator*(const vec3 &lhs, const double rhs)
{
    return vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

inline vec3 operator*(const double lhs, const vec3 &rhs)
{
    return rhs * lhs;
}

inline vec3 operator/(const vec3 &lhs, const double rhs)
{
    return lhs * (1 / rhs);
}

inline double dot(const vec3 &lhs, const vec3 &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

inline double dot(const vec3 &v)
{
    return dot(v, v);
}

inline double length(const vec3 &v)
{
    return std::sqrt(dot(v));
}

inline vec3 normalise(const vec3 &v)
{
    return v / length(v);
}

vec3 randomUnitSphere();
vec3 randomUnitVector();
vec3 randomHemisphere(const vec3 &normal);
