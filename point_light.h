#ifndef QUARKENGINE_POINT_LIGHT_H
#define QUARKENGINE_POINT_LIGHT_H

#include "object.h"

typedef struct {
    Vec4 position;
    Vec4 ambient;
    Vec4 diffuse;
    Vec4 specular;
    float constant;
    float linear;
    float quadratic;
    Object *object;
} PointLight;

PointLight *point_light_new(Vec4 position, Vec4 ambient, Vec4 diffuse, Vec4 specular,
                            float constant, float linear, float quadratic);
void point_light_delete(PointLight *self);
void point_light_use(PointLight *self, Shader *object_shader, Shader *light_shader, int n);

#endif
