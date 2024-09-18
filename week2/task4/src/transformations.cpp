#include "transformations.hpp"
#include "utils.h"

color gradient_vertical(const color& color_start, const color& color_end, int j) {
    double t = double(j) / (HEIGHT - 1);
    return color_start.scale(1.0 - t).add(color_end.scale(t));
}

color gradient_horizontal(const color& color_start, const color& color_end, int i) {
    double t = double(i) / (WIDTH - 1);
    return color_start.scale(1.0 - t).add(color_end.scale(t));
}

color invert_color(const color& c) {
    return color(1.0 - c.x(), 1.0 - c.y(), 1.0 - c.z());
}

color color2bw(const color& c) {
    double gray = 0.2989 * c.x() + 0.5870 * c.y() + 0.1140 * c.z();
    return color(gray, gray, gray);
}