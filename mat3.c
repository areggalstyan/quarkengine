#include <math.h>
#include "mat3.h"

Mat3 mat3(float a, float b, float c,
          float d, float e, float f,
          float g, float h, float i) {
    return (Mat3) {
        a, b, c,
        d, e, f,
        g, h, i
    };
}

Mat3 mat3_add(Mat3 a, Mat3 b) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a.m[i][j] += b.m[i][j];
        }
    }
    return a;
}

Mat3 mat3_mul(Mat3 a, Mat3 b) {
    Mat3 c = {};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                c.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return c;
}

Mat3 mat3_muls(Mat3 a, float b) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a.m[i][j] *= b;
        }
    }
    return a;
}

Vec3 mat3_mulv(Mat3 a, Vec3 b) {
    return (Vec3) {
        a.m[0][0] * b.x + a.m[0][1] * b.y + a.m[0][2] * b.z,
        a.m[1][0] * b.x + a.m[1][1] * b.y + a.m[1][2] * b.z,
        a.m[2][0] * b.x + a.m[2][1] * b.y + a.m[2][2] * b.z
    };
}

Mat3 mat3_scale(Vec3 scale) {
    return mat3(scale.x, 0, 0,
                0, scale.y, 0,
                0, 0, 1);
}

Mat3 mat3_rotate(float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    return mat3(c, -s, 0,
                s, c, 0,
                0, 0, 1);
}

Mat3 mat3_translate(Vec3 translation) {
    return mat3(1, 0, translation.x,
                0, 1, translation.y,
                0, 0, 1);
}
