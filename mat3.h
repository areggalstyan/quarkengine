#ifndef QUARKENGINE_MAT3_H
#define QUARKENGINE_MAT3_H

#include "vec3.h"

typedef struct {
    float m[3][3];
} Mat3;

Mat3 mat3(float a, float b, float c,
          float d, float e, float f,
          float g, float h, float i);
Mat3 mat3_add(Mat3 a, Mat3 b);
Mat3 mat3_mul(Mat3 a, Mat3 b);
Mat3 mat3_muls(Mat3 a, float b);
Vec3 mat3_mulv(Mat3 a, Vec3 b);
Mat3 mat3_scale(Vec3 scale);
Mat3 mat3_rotate(float angle);
Mat3 mat3_translate(Vec3 translation);

#endif
