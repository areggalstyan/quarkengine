#ifndef QUARKENGINE_DIRECTIONAL_LIGHT_H
#define QUARKENGINE_DIRECTIONAL_LIGHT_H

#include "shader.h"

typedef struct {
    Vec4 direction;
    Vec4 ambient;
    Vec4 diffuse;
    Vec4 specular;
} DirectionalLight;

DirectionalLight *directional_light_new(Vec4 direction, Vec4 ambient, Vec4 diffuse, Vec4 specular);
void directional_light_delete(DirectionalLight *self);
void directional_light_use(DirectionalLight *self, Shader *shader, int n);

#endif
