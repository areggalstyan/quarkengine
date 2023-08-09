#include <math.h>
#include "vec3.h"

Vec3 vec3(float x, float y) {
    return (Vec3) {x, y};
}

Vec3 vec3_adds(Vec3 a, float b) {
    return vec3_add(a, vec3(b, b));
}

Vec3 vec3_subs(Vec3 a, float b) {
    return vec3_adds(a, -b);
}

Vec3 vec3_muls(Vec3 a, float b) {
    return vec3(a.x * b, a.y * b);
}

Vec3 vec3_divs(Vec3 a, float b) {
    return vec3_muls(a, 1 / b);
}

Vec3 vec3_add(Vec3 a, Vec3 b) {
    return vec3(a.x + b.x, a.y + b.y);
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return vec3_add(a, vec3_negate(b));
}

Vec3 vec3_negate(Vec3 a) {
    return vec3_muls(a, -1);
}

Vec3 vec3_normalize(Vec3 a) {
    return vec3_divs(a, vec3_magnitude(a));
}

float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y;
}

float vec3_distance(Vec3 a, Vec3 b) {
    Vec3 d = vec3_sub(a, b);
    return sqrtf(vec3_dot(d, d));
}

float vec3_magnitude(Vec3 a) {
    return vec3_distance(vec3(0, 0), a);
}
