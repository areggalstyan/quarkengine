#include <stdlib.h>
#include <stdio.h>
#include "spotlight.h"

Spotlight *spotlight_new(Vec4 position, Vec4 direction, float inner, float outer,
                         Vec4 ambient, Vec4 diffuse, Vec4 specular) {
    Spotlight *self = malloc(sizeof *self);
    self->position = position;
    self->direction = direction;
    self->inner = inner;
    self->outer = outer;
    self->ambient = ambient;
    self->diffuse = diffuse;
    self->specular = specular;
    Shape *shape = shape_cube(1);
    Material *material = material_new(vec4(0, 0, 0),
                                      vec4(0, 0, 0),
                                      vec4(0, 0, 0), 0);
    Prefab *prefab = prefab_new(position, shape, material);
    shape_delete(shape);
    material_delete(material);
    self->object = object_new(prefab);
    prefab_delete(prefab);
    return self;
}

void spotlight_delete(Spotlight *self) {
    object_delete(self->object);
    free(self);
}

void spotlight_use(Spotlight *self, Shader *object_shader, Shader *light_shader, int n) {
    shader_use(light_shader);
    object_draw(self->object, light_shader);
    shader_use(object_shader);
    char position[25];
    sprintf(position, "u_spotlights[%d].position", n);
    shader_set_uniform_vec4(object_shader, position, self->position);
    char direction[26];
    sprintf(direction, "u_spotlights[%d].direction", n);
    shader_set_uniform_vec4(object_shader, direction, self->direction);
    char inner[22];
    sprintf(inner, "u_spotlights[%d].inner", n);
    shader_set_uniform_float(object_shader, inner, self->inner);
    char outer[22];
    sprintf(outer, "u_spotlights[%d].outer", n);
    shader_set_uniform_float(object_shader, outer, self->outer);
    char ambient[24];
    sprintf(ambient, "u_spotlights[%d].ambient", n);
    shader_set_uniform_vec4(object_shader, ambient, self->ambient);
    char diffuse[24];
    sprintf(diffuse, "u_spotlights[%d].diffuse", n);
    shader_set_uniform_vec4(object_shader, diffuse, self->diffuse);
    char specular[25];
    sprintf(specular, "u_spotlights[%d].specular", n);
    shader_set_uniform_vec4(object_shader, specular, self->specular);
}
