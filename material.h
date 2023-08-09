#ifndef QUARKENGINE_MATERIAL_H
#define QUARKENGINE_MATERIAL_H

#include "shader.h"
#include "vec4.h"

typedef struct {
    Vec4 ambient;
    Vec4 diffuse;
    Vec4 specular;
    float shininess;
} Material;

Material *material_new(Vec4 ambient, Vec4 diffuse, Vec4 specular, float shininess);
void material_delete(Material *self);

#endif
