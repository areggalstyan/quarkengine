#include <stdlib.h>
#include <math.h>
#include <glad/glad.h>
#include "camera.h"

Camera *camera_new(Vec4 position, Vec4 direction, float speed, float fov, float near, float far) {
    Camera *self = malloc(sizeof *self);
    self->position = position;
    self->direction = direction;
    self->speed = speed;
    self->fov = fov;
    self->near = near;
    self->far = far;
    return self;
}

void camera_delete(Camera *self) {
    free(self);
}

static Mat4 get_view(Camera *self) {
    Vec4 f, r, u;
    camera_get_directions(self, &f, &r, &u);
    return mat4(r.x, r.y, r.z, -vec4_dot(self->position, r),
                u.x, u.y, u.z, -vec4_dot(self->position, u),
                f.x, f.y, f.z, -vec4_dot(self->position, f),
                0, 0, 0, 1);
}

static Mat4 get_projection(Camera *self) {
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    float a = (float) viewport[3] / (float) viewport[2];
    float t = tanf(self->fov / 2);
    float n = self->near;
    float f = self->far;
    return mat4(a / t, 0, 0, 0,
                0, 1 / t, 0, 0,
                0, 0, (n + f) / (n - f), 2 * n * f / (n - f),
                0, 0, -1, 0);
}

void camera_use(Camera *self, Shader *shader) {
    shader_set_uniform_mat4(shader, "u_view", get_view(self));
    shader_set_uniform_mat4(shader, "u_projection", get_projection(self));
    shader_set_uniform_vec4(shader, "u_camera", self->position);
}

void camera_get_directions(Camera *self, Vec4 *forward, Vec4 *right, Vec4 *up) {
    *forward = vec4_normalize(self->direction);
    *right = vec4_normalize(vec4_cross(*forward, vec4(0, 1, 0)));
    *up = vec4_normalize(vec4_cross(*right, *forward));
}

void camera_move_towards(Camera *self, Vec4 target, float delta) {
    self->position = vec4_add(self->position, vec4_muls(target, delta * self->speed));
}

void camera_look_at(Camera *self, Vec4 target) {
    self->direction = vec4_negate(target);
}
