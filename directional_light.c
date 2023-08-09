#include <stdlib.h>
#include <stdio.h>
#include "directional_light.h"

DirectionalLight *directional_light_new(Vec4 direction, Vec4 ambient, Vec4 diffuse, Vec4 specular) {
    DirectionalLight *self = malloc(sizeof *self);
    self->direction = direction;
    self->ambient = ambient;
    self->diffuse = diffuse;
    self->specular = specular;
    return self;
}

void directional_light_delete(DirectionalLight *self) {
    free(self);
}

void directional_light_use(DirectionalLight *self, Shader *shader, int n) {
    char direction[34];
    sprintf(direction, "u_directional_lights[%d].direction", n);
    shader_set_uniform_vec4(shader, direction, self->direction);
    char ambient[32];
    sprintf(ambient, "u_directional_lights[%d].ambient", n);
    shader_set_uniform_vec4(shader, ambient, self->ambient);
    char diffuse[32];
    sprintf(diffuse, "u_directional_lights[%d].diffuse", n);
    shader_set_uniform_vec4(shader, diffuse, self->diffuse);
    char specular[33];
    sprintf(specular, "u_directional_lights[%d].specular", n);
    shader_set_uniform_vec4(shader, specular, self->specular);
}
