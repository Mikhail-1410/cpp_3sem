#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include "vec3.h"

using color = vec3;

color gradient_vertical(const color& color_start, const color& color_end, int j);
color gradient_horizontal(const color& color_start, const color& color_end, int i);
color invert_color(const color& c);
color color2bw(const color& c);

#endif // TRANSFORMATIONS_HPP
