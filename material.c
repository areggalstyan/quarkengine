#include <stdlib.h>
#include "material.h"

Material *material_new(Vec4 ambient, Vec4 diffuse, Vec4 specular, float shininess) {
    Material *self = malloc(sizeof *self);
    self->ambient = ambient;
    self->diffuse = diffuse;
    self->specular = specular;
    self->shininess = shininess;
    return self;
}

void material_delete(Material *self) {
    free(self);
}
