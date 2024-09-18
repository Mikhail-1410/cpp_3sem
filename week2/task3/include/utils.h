#ifndef UTILS_H
#define UTILS_H

#ifndef WIDTH
#define WIDTH 480
#endif

#ifndef HEIGHT
#define HEIGHT 320
#endif

#include "vec3.h"
#include <iostream>
#include <string>

using color = vec3;

void write_image(const std::string& path);

void write_color(std::ostream& out, const color& pixel_color);

#endif //UTILS_H