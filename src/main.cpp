#include <iostream>
#include <color.hpp>
#include <vec3.hpp>

int main()
{
    const int width = 256;
    const int height = 256;

    std::cout << "P3\n"
              << width << ' ' << height << " 255" << std::endl;

    for (int y = height - 1; y >= 0; --y)
    {
        std::cerr << "\rScanlines remaining: " << y << '\n'
                  << std::flush;
        for (int x = 0; x < width; x++)
        {
            color3 pixel(double(x) / (width - 1), double(y) / (height - 1), 0.25);
            writeColor(std::cout, pixel);
        }
    }

    std::cerr << "\nDone!\n";
    return 0;
}