#ifndef QUARKENGINE_CAMERA_H
#define QUARKENGINE_CAMERA_H

#include "shader.h"

typedef struct {
    Vec4 position;
    Vec4 direction;
    float speed;
    float fov;
    float near;
    float far;
} Camera;

Camera *camera_new(Vec4 position, Vec4 direction, float speed, float fov, float near, float far);
void camera_delete(Camera *self);
void camera_use(Camera *self, Shader *shader);
void camera_get_directions(Camera *self, Vec4 *forward, Vec4 *right, Vec4 *up);
void camera_move_towards(Camera *self, Vec4 target, float delta);
void camera_look_at(Camera *self, Vec4 target);

#endif
