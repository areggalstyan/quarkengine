#ifndef QUARKENGINE_VEC3_H
#define QUARKENGINE_VEC3_H

typedef struct {
    float x, y, z;
} Vec3;

Vec3 vec3(float x, float y);
Vec3 vec3_adds(Vec3 a, float b);
Vec3 vec3_subs(Vec3 a, float b);
Vec3 vec3_muls(Vec3 a, float b);
Vec3 vec3_divs(Vec3 a, float b);
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_negate(Vec3 a);
Vec3 vec3_normalize(Vec3 a);
float vec3_dot(Vec3 a, Vec3 b);
float vec3_distance(Vec3 a, Vec3 b);
float vec3_magnitude(Vec3 a);

#endif
