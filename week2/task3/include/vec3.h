#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <string>

class vec3 {
public:
    vec3() : e{0, 0, 0} {}

    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    double get(int idx) const { return e[idx]; }

    vec3& add(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& sub(const vec3& v) {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
    }

    vec3& scale(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    double dot(const vec3& v) const {
        return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
    }

    vec3 cross(const vec3& v) const {
        return vec3(
            e[1] * v.e[2] - e[2] * v.e[1],
            e[2] * v.e[0] - e[0] * v.e[2],
            e[0] * v.e[1] - e[1] * v.e[0]
        );
    }

    std::string print() const {
        return std::to_string(e[0]) + " " + std::to_string(e[1]) + " " + std::to_string(e[2]);
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

private:
    double e[3];
};

#endif // VEC3_H
