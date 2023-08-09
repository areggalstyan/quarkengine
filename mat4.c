#include <math.h>
#include "mat4.h"

Mat4 mat4(float a, float b, float c, float d,
          float e, float f, float g, float h,
          float i, float j, float k, float l,
          float m, float n, float o, float p) {
    return (Mat4) {
        a, b, c, d,
        e, f, g, h,
        i, j, k, l,
        m, n, o, p
    };
}

Mat4 mat4_add(Mat4 a, Mat4 b) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            a.m[i][j] += b.m[i][j];
        }
    }
    return a;
}

Mat4 mat4_mul(Mat4 a, Mat4 b) {
    Mat4 c = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                c.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return c;
}

Mat4 mat4_muls(Mat4 a, float b) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            a.m[i][j] *= b;
        }
    }
    return a;
}

Vec4 mat4_mulv(Mat4 a, Vec4 b) {
    return (Vec4) {
        a.m[0][0] * b.x + a.m[0][1] * b.y + a.m[0][2] * b.z + a.m[0][3] * b.w,
        a.m[1][0] * b.x + a.m[1][1] * b.y + a.m[1][2] * b.z + a.m[1][3] * b.w,
        a.m[2][0] * b.x + a.m[2][1] * b.y + a.m[2][2] * b.z + a.m[2][3] * b.w,
        a.m[3][0] * b.x + a.m[3][1] * b.y + a.m[3][2] * b.z + a.m[3][3] * b.w
    };
}

Mat4 mat4_scale(Vec4 scale) {
    return mat4(scale.x, 0, 0, 0,
                0, scale.y, 0, 0,
                0, 0, scale.z, 0,
                0, 0, 0, 1);
}

Mat4 mat4_rotate(float angle, Vec4 axis) {
    Vec4 a = vec4_normalize(axis);
    float c = cosf(angle);
    float s = sinf(angle);
    float c1 = 1 - c;
    return mat4(c1 * a.x * a.x + c, c1 * a.x * a.y - a.z * s, c1 * a.x * a.z + a.y * s, 0,
                c1 * a.x * a.y + a.z * s, c1 * a.y * a.y + c, c1 * a.y * a.z - a.x * s, 0,
                c1 * a.x * a.z - a.y * s, c1 * a.y * a.z + a.x * s, c1 * a.z * a.z + c, 0,
                0, 0, 0, 1);
}

Mat4 mat4_translate(Vec4 translation) {
    return mat4(1, 0, 0, translation.x,
                0, 1, 0, translation.y,
                0, 0, 1, translation.z,
                0, 0, 0, 1);
}
