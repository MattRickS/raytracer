#pragma once
#include <vec3.hpp>
#include <utils.hpp>

inline double trilinear_interpolation(double c[2][2][2], double u, double v, double w)
{
    double accum = 0.0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                accum += (i * u + (1 - i) * (1 - u)) *
                         (j * v + (1 - j) * (1 - v)) *
                         (k * w + (1 - k) * (1 - w)) * c[i][j][k];
            }
        }
    }
    return accum;
}

class Perlin
{
public:
    Perlin()
    {
        ranfloat = new vec3[point_count];
        for (int i = 0; i < point_count; ++i)
        {
            ranfloat[i] = normalise(vec3::random(-1, 1));
        }

        perm_x = perlinGeneratePerm();
        perm_y = perlinGeneratePerm();
        perm_z = perlinGeneratePerm();
    }

    ~Perlin()
    {
        delete[] ranfloat;
        delete[] perm_x;
        delete[] perm_y;
        delete[] perm_z;
    }

    double noise(const point3 &pos) const
    {
        double u = pos.x - floor(pos.x);
        double v = pos.y - floor(pos.y);
        double w = pos.z - floor(pos.z);

        int i = floor(pos.x);
        int j = floor(pos.y);
        int k = floor(pos.z);

        vec3 c[2][2][2];

        for (int di = 0; di < 2; di++)
        {
            for (int dj = 0; dj < 2; dj++)
            {
                for (int dk = 0; dk < 2; dk++)
                {
                    c[di][dj][dk] = ranfloat[perm_x[(i + di) & 255] ^
                                             perm_x[(j + dj) & 255] ^
                                             perm_x[(k + dk) & 255]];
                }
            }
        }

        return perlin_interpolation(c, u, v, w);
    }

    double turb(const point3 &pos, int depth = 7) const
    {
        double accum = 0.0;
        auto temp_p = pos;
        double weight = 1.0;

        for (int i = 0; i < depth; i++)
        {
            accum += weight * noise(temp_p);
            weight *= 0.5;
            temp_p *= 2;
        }

        return fabs(accum);
    }

private:
    static const int point_count = 256;
    vec3 *ranfloat;
    int *perm_x;
    int *perm_y;
    int *perm_z;

    static int *perlinGeneratePerm()
    {
        auto p = new int[point_count];

        for (int i = 0; i < point_count; i++)
        {
            p[i] = i;
        }

        permute(p, point_count);
        return p;
    }

    static void permute(int *p, int n)
    {
        for (int i = n - 1; i > 0; i--)
        {
            int target = randInt(0, i);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }

    inline double perlin_interpolation(vec3 c[2][2][2], double u, double v, double w) const
    {
        double uu = u * u * (3 - 2 * u);
        double vv = v * v * (3 - 2 * v);
        double ww = w * w * (3 - 2 * w);
        double accum = 0.0;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    vec3 weight_v(u - i, v - j, w - k);
                    accum += (i * uu + (1 - i) * (1 - uu)) *
                             (j * vv + (1 - j) * (1 - vv)) *
                             (k * ww + (1 - k) * (1 - ww)) *
                             dot(c[i][j][k], weight_v);
                }
            }
        }
        return accum;
    }
};
