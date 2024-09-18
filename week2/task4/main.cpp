#include "utils.h"
#include "transformations.hpp"
#include <fstream>  

int main() {
    std::string path("my_image.ppm");
    
    color color_start(1.0, 0.0, 0.0);
    color color_end(0.0, 0.0, 1.0);

    std::ofstream os(path);
    os << "P3\n" << HEIGHT << ' ' << WIDTH << "\n255\n";

    for (int j = 0; j < 320; j++) {
        for (int i = 0; i < 480; i++) {
            color pixel_color = gradient_vertical(color_start, color_end, j);
            write_color(os, pixel_color);
        }
    }

    return 0;
}