#ifndef QUARKENGINE_SPOTLIGHT_H
#define QUARKENGINE_SPOTLIGHT_H

#include "object.h"

typedef struct {
    Vec4 position;
    Vec4 direction;
    float inner;
    float outer;
    Vec4 ambient;
    Vec4 diffuse;
    Vec4 specular;
    Object *object;
} Spotlight;

Spotlight *spotlight_new(Vec4 position, Vec4 direction, float inner, float outer,
                         Vec4 ambient, Vec4 diffuse, Vec4 specular);
void spotlight_delete(Spotlight *self);
void spotlight_use(Spotlight *self, Shader *object_shader, Shader *light_shader, int n);

#endif
