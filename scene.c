#include <stdlib.h>
#include <string.h>
#include "scene.h"

Scene *scene_new(Shader *object_shader, Shader *light_shader, Camera *camera) {
    Scene *self = malloc(sizeof *self);
    self->object_shader = object_shader;
    self->light_shader = light_shader;
    self->camera = camera;
    self->objects = NULL;
    self->nobjects = 0;
    self->directional_lights = NULL;
    self->ndirectional_lights = 0;
    self->point_lights = NULL;
    self->npoint_lights = 0;
    self->spotlights = NULL;
    self->nspotlights = 0;
    return self;
}

void scene_delete(Scene *self) {
    if (self->objects != NULL) {
        free(self->objects);
    }
    if (self->directional_lights != NULL) {
        free(self->directional_lights);
    }
    if (self->point_lights != NULL) {
        free(self->point_lights);
    }
    if (self->spotlights != NULL) {
        free(self->spotlights);
    }
    free(self);
}

void scene_add_object(Scene *self, Object *object) {
    Object **objects = self->objects;
    self->objects = malloc((self->nobjects + 1) * sizeof object);
    self->objects[self->nobjects] = object;
    if (objects != NULL) {
        memcpy(self->objects, objects, self->nobjects * sizeof object);
        free(objects);
    }
    self->nobjects++;
}

void scene_add_directional_light(Scene *self, DirectionalLight *directional_light) {
    DirectionalLight **directional_lights = self->directional_lights;
    self->directional_lights = malloc((self->ndirectional_lights + 1) * sizeof directional_light);
    self->directional_lights[self->ndirectional_lights] = directional_light;
    if (directional_lights != NULL) {
        memcpy(self->directional_lights, directional_lights, self->ndirectional_lights * sizeof directional_light);
        free(directional_lights);
    }
    self->ndirectional_lights++;
}

void scene_add_point_light(Scene *self, PointLight *point_light) {
    PointLight **point_lights = self->point_lights;
    self->point_lights = malloc((self->npoint_lights + 1) * sizeof point_light);
    self->point_lights[self->npoint_lights] = point_light;
    if (point_lights != NULL) {
        memcpy(self->point_lights, point_lights, self->npoint_lights * sizeof point_light);
        free(point_lights);
    }
    self->npoint_lights++;
}

void scene_add_spotlight(Scene *self, Spotlight *spotlight) {
    Spotlight **spotlights = self->spotlights;
    self->spotlights = malloc((self->nspotlights + 1) * sizeof spotlight);
    self->spotlights[self->nspotlights] = spotlight;
    if (spotlights != NULL) {
        memcpy(self->spotlights, spotlights, self->nspotlights * sizeof spotlight);
        free(spotlights);
    }
    self->nspotlights++;
}

void scene_draw(Scene *self) {
    shader_use(self->light_shader);
    camera_use(self->camera, self->light_shader);
    shader_use(self->object_shader);
    camera_use(self->camera, self->object_shader);
    for (int i = 0; i < self->ndirectional_lights; i++) {
        directional_light_use(self->directional_lights[i], self->object_shader, i);
    }
    shader_set_uniform_int(self->object_shader, "u_ndirectional_lights", self->ndirectional_lights);
    for (int i = 0; i < self->npoint_lights; i++) {
        point_light_use(self->point_lights[i], self->object_shader, self->light_shader, i);
    }
    shader_set_uniform_int(self->object_shader, "u_npoint_lights", self->npoint_lights);
    for (int i = 0; i < self->nspotlights; i++) {
        spotlight_use(self->spotlights[i], self->object_shader, self->light_shader, i);
    }
    shader_set_uniform_int(self->object_shader, "u_nspotlights", self->nspotlights);
    for (int i = 0; i < self->nobjects; i++) {
        object_draw(self->objects[i], self->object_shader);
    }
}
