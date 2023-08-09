#ifndef QUARKENGINE_PREFAB_H
#define QUARKENGINE_PREFAB_H

#include "shape.h"
#include "material.h"

typedef struct {
    Vec4 position;
    Shape *shape;
    Material *material;
} Prefab;

Prefab *prefab_new(Vec4 position, Shape *shape, Material *material);
void prefab_delete(Prefab *self);

#endif
