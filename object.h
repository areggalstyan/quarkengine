#ifndef QUARKENGINE_OBJECT_H
#define QUARKENGINE_OBJECT_H

#include "prefab.h"

typedef struct {
    unsigned int vao;
    int count;
    Material *material;
    Vec4 position;
    Mat4 model;
} Object;

Object *object_new(Prefab *prefab);
void object_delete(Object *self);
void object_draw(Object *self, Shader *shader);
void object_transform(Object *self, Mat4 transformation);
void object_scale(Object *self, Vec4 scale);
void object_rotate_global(Object *self, float angle, Vec4 axis);
void object_rotate_local(Object *self, float angle, Vec4 axis);
void object_translate(Object *self, Vec4 translation);
void object_reset(Object *self);

#endif
