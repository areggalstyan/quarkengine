#include <stdlib.h>
#include <string.h>
#include "glad/glad.h"
#include "object.h"

static unsigned int create_vao(Shape *shape) {
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, shape->nvertices, shape->vertices, GL_STATIC_DRAW);
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape->nindices, shape->indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (4 * sizeof(float)));
    glEnableVertexAttribArray(1);
    return vao;
}

Object *object_new(Prefab *prefab) {
    Object *self = malloc(sizeof *self);
    self->vao = create_vao(prefab->shape);
    self->count = prefab->shape->nindices / (int) sizeof *prefab->shape->indices;
    self->material = malloc(sizeof *prefab->material);
    memcpy(self->material, prefab->material, sizeof *self->material);
    self->position = prefab->position;
    object_reset(self);
    return self;
}

void object_delete(Object *self) {
    material_delete(self->material);
    free(self);
}

void object_draw(Object *self, Shader *shader) {
    shader_set_uniform_mat4(shader, "u_model", self->model);
    shader_set_uniform_vec4(shader, "u_material.ambient", self->material->ambient);
    shader_set_uniform_vec4(shader, "u_material.diffuse", self->material->diffuse);
    shader_set_uniform_vec4(shader, "u_material.specular", self->material->specular);
    shader_set_uniform_float(shader, "u_material.shininess", self->material->shininess);
    glBindVertexArray(self->vao);
    glDrawElements(GL_TRIANGLES, self->count, GL_UNSIGNED_INT, 0);
}

void object_transform(Object *self, Mat4 transformation) {
    self->model = mat4_mul(transformation, self->model);
}

void object_scale(Object *self, Vec4 scale) {
    object_transform(self, mat4_scale(scale));
}

void object_rotate_global(Object *self, float angle, Vec4 axis) {
    object_transform(self, mat4_rotate(angle, axis));
}

void object_rotate_local(Object *self, float angle, Vec4 axis) {
    object_translate(self, vec4_negate(self->position));
    object_rotate_global(self, angle, axis);
    object_translate(self, self->position);
}

void object_translate(Object *self, Vec4 translation) {
    object_transform(self, mat4_translate(translation));
}

void object_reset(Object *self) {
    self->model = mat4_translate(self->position);
}
