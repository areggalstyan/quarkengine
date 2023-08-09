#ifndef QUARKENGINE_VEC4_H
#define QUARKENGINE_VEC4_H

typedef struct {
    float x, y, z, w;
} Vec4;

Vec4 vec4(float x, float y, float z);
Vec4 vec4_adds(Vec4 a, float b);
Vec4 vec4_subs(Vec4 a, float b);
Vec4 vec4_muls(Vec4 a, float b);
Vec4 vec4_divs(Vec4 a, float b);
Vec4 vec4_add(Vec4 a, Vec4 b);
Vec4 vec4_sub(Vec4 a, Vec4 b);
Vec4 vec4_cross(Vec4 a, Vec4 b);
Vec4 vec4_negate(Vec4 a);
Vec4 vec4_normalize(Vec4 a);
float vec4_dot(Vec4 a, Vec4 b);
float vec4_distance(Vec4 a, Vec4 b);
float vec4_magnitude(Vec4 a);

#endif
