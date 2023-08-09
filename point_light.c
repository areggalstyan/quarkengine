#include <stdlib.h>
#include <stdio.h>
#include "point_light.h"

PointLight *point_light_new(Vec4 position, Vec4 ambient, Vec4 diffuse, Vec4 specular,
                            float constant, float linear, float quadratic) {
    PointLight *self = malloc(sizeof *self);
    self->position = position;
    self->ambient = ambient;
    self->diffuse = diffuse;
    self->specular = specular;
    self->constant = constant;
    self->linear = linear;
    self->quadratic = quadratic;
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

void point_light_delete(PointLight *self) {
    object_delete(self->object);
    free(self);
}

void point_light_use(PointLight *self, Shader *object_shader, Shader *light_shader, int n) {
    shader_use(light_shader);
    object_draw(self->object, light_shader);
    shader_use(object_shader);
    char position[27];
    sprintf(position, "u_point_lights[%d].position", n);
    shader_set_uniform_vec4(object_shader, position, self->position);
    char ambient[26];
    sprintf(ambient, "u_point_lights[%d].ambient", n);
    shader_set_uniform_vec4(object_shader, ambient, self->ambient);
    char diffuse[26];
    sprintf(diffuse, "u_point_lights[%d].diffuse", n);
    shader_set_uniform_vec4(object_shader, diffuse, self->diffuse);
    char specular[27];
    sprintf(specular, "u_point_lights[%d].specular", n);
    shader_set_uniform_vec4(object_shader, specular, self->specular);
    char constant[27];
    sprintf(constant, "u_point_lights[%d].constant", n);
    shader_set_uniform_float(object_shader, constant, self->constant);
    char linear[25];
    sprintf(linear, "u_point_lights[%d].linear", n);
    shader_set_uniform_float(object_shader, linear, self->linear);
    char quadratic[28];
    sprintf(quadratic, "u_point_lights[%d].quadratic", n);
    shader_set_uniform_float(object_shader, quadratic, self->quadratic);
}
