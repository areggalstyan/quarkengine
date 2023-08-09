#ifndef QUARKENGINE_MAT4_H
#define QUARKENGINE_MAT4_H

#include "vec4.h"

typedef struct {
    float m[4][4];
} Mat4;

Mat4 mat4(float a, float b, float c, float d,
          float e, float f, float g, float h,
          float i, float j, float k, float l,
          float m, float n, float o, float p);
Mat4 mat4_add(Mat4 a, Mat4 b);
Mat4 mat4_mul(Mat4 a, Mat4 b);
Mat4 mat4_muls(Mat4 a, float b);
Vec4 mat4_mulv(Mat4 a, Vec4 b);
Mat4 mat4_scale(Vec4 scale);
Mat4 mat4_rotate(float angle, Vec4 axis);
Mat4 mat4_translate(Vec4 translation);

#endif
