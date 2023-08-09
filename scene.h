#ifndef QUARKENGINE_SCENE_H
#define QUARKENGINE_SCENE_H

#include "camera.h"
#include "object.h"
#include "directional_light.h"
#include "point_light.h"
#include "spotlight.h"

typedef struct {
    Shader *object_shader;
    Shader *light_shader;
    Camera *camera;
    Object **objects;
    int nobjects;
    DirectionalLight **directional_lights;
    int ndirectional_lights;
    PointLight **point_lights;
    int npoint_lights;
    Spotlight **spotlights;
    int nspotlights;
} Scene;

Scene *scene_new(Shader *object_shader, Shader *light_shader, Camera *camera);
void scene_delete(Scene *self);
void scene_add_object(Scene *self, Object *object);
void scene_add_directional_light(Scene *self, DirectionalLight *directional_light);
void scene_add_point_light(Scene *self, PointLight *point_light);
void scene_add_spotlight(Scene *self, Spotlight *spotlight);
void scene_draw(Scene *self);

#endif
