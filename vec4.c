#include <math.h>
#include "vec4.h"

Vec4 vec4(float x, float y, float z) {
    return (Vec4) {x, y, z, 1};
}

Vec4 vec4_adds(Vec4 a, float b) {
    return vec4_add(a, vec4(b, b, b));
}

Vec4 vec4_subs(Vec4 a, float b) {
    return vec4_adds(a, -b);
}

Vec4 vec4_muls(Vec4 a, float b) {
    return vec4(a.x * b, a.y * b, a.z * b);
}

Vec4 vec4_divs(Vec4 a, float b) {
    return vec4_muls(a, 1 / b);
}

Vec4 vec4_add(Vec4 a, Vec4 b) {
    return vec4(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec4 vec4_sub(Vec4 a, Vec4 b) {
    return vec4_add(a, vec4_negate(b));
}

Vec4 vec4_cross(Vec4 a, Vec4 b) {
    return vec4(a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

Vec4 vec4_negate(Vec4 a) {
    return vec4_muls(a, -1);
}

Vec4 vec4_normalize(Vec4 a) {
    return vec4_divs(a, vec4_magnitude(a));
}

float vec4_dot(Vec4 a, Vec4 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec4_distance(Vec4 a, Vec4 b) {
    Vec4 d = vec4_sub(a, b);
    return sqrtf(vec4_dot(d, d));
}

float vec4_magnitude(Vec4 a) {
    return vec4_distance(vec4(0, 0, 0), a);
}
