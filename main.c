#include <math.h>
#include "window.h"

int main(void) {
    Window *window = window_new("QuarkEngine", 800, 600);
    Shader *object_shader = shader_new("object.vert", "object.frag");
    Shader *light_shader = shader_new("light.vert", "light.frag");
    Camera *camera = camera_new(vec4(0, 0, 0), vec4(0.5f, 0, -1),
                                10, M_PI_2, 1, 100);
    Spotlight *spotlight = spotlight_new(vec4(0, 0, 12),
                                         vec4(0, -1, 0),
                                         cosf(M_PI_4), cosf(M_PI_2),
                                         vec4(0.25f, 0.25f, 0.25f),
                                         vec4(0.5f, 0.5f, 0.5f),
                                         vec4(0.75f, 0.75f, 0.75f));
    PointLight *point_light_1 = point_light_new(vec4(-10, -2, 12),
                                                vec4(0.25f, 0.25f, 0.25f),
                                                vec4(0.5f, 0.5f, 0.5f),
                                                vec4(0.75f, 0.75f, 0.75f),
                                                1, 0.07f, 0.017f);
    PointLight *point_light_2 = point_light_new(vec4(10, -2, 12),
                                              vec4(0.25f, 0.25f, 0.25f),
                                              vec4(0.5f, 0.5f, 0.5f),
                                              vec4(0.75f, 0.75f, 0.75f),
                                              1, 0.07f, 0.017f);
    DirectionalLight *directional_light = directional_light_new(vec4(0, -1, -1),
                                                                vec4(0.125f, 0.125f, 0.125f),
                                                                vec4(0.25f, 0.25f, 0.25f),
                                                                vec4(0.325f, 0.325f, 0.325f));
    Scene *scene = scene_new(object_shader, light_shader, camera);
    scene_add_spotlight(scene, spotlight);
    scene_add_point_light(scene, point_light_1);
    scene_add_point_light(scene, point_light_2);
    scene_add_directional_light(scene, directional_light);
    Shape *shape = shape_cube(1);
    Material *material = material_new(vec4(0.25f, 0.25f, 0.25f),
                                      vec4(0.75f, 0.75f, 0.75f),
                                      vec4(0.75f, 0.75f, 0.75f), 16);
    Prefab *prefab = prefab_new(vec4(0, 0, 3), shape, material);
    shape_delete(shape);
    material_delete(material);
    Object *object = object_new(prefab);
    prefab_delete(prefab);
    scene_add_object(scene, object);
    window_set_scene(window, scene);
    while (window_is_open(window)) {
        object_reset(object);
        object_scale(object, vec4(30, 1, 4));
        object_translate(object, vec4(0, -6, 0));
        window_draw(window);
    }
    window_delete(window);
    shader_delete(object_shader);
    shader_delete(light_shader);
    camera_delete(camera);
    spotlight_delete(spotlight);
    point_light_delete(point_light_1);
    point_light_delete(point_light_2);
    directional_light_delete(directional_light);
    scene_delete(scene);
    object_delete(object);
    return 0;
}
