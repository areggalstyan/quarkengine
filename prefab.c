#include <stdlib.h>
#include <string.h>
#include "prefab.h"

Prefab *prefab_new(Vec4 position, Shape *shape, Material *material) {
    Prefab *self = malloc(sizeof *self);
    self->position = position;
    self->shape = malloc(sizeof *shape);
    memcpy(self->shape, shape, sizeof *shape);
    self->shape->vertices = malloc(shape->nvertices);
    memcpy(self->shape->vertices, shape->vertices, shape->nvertices);
    self->shape->indices = malloc(shape->nindices);
    memcpy(self->shape->indices, shape->indices, shape->nindices);
    self->material = malloc(sizeof *material);
    memcpy(self->material, material, sizeof *material);
    return self;
}

void prefab_delete(Prefab *self) {
    shape_delete(self->shape);
    material_delete(self->material);
    free(self);
}
