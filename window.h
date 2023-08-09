#ifndef QUARKENGINE_WINDOW_H
#define QUARKENGINE_WINDOW_H

#include <stdbool.h>
#include "GLFW/glfw3.h"
#include "scene.h"

typedef struct Window {
    GLFWwindow *window;
    Scene *scene;
    float delta;
} Window;

Window *window_new(char *title, int width, int height);
void window_delete(Window *self);
void window_set_scene(Window *self, Scene *scene);
bool window_is_open(Window *self);
void window_draw(Window *self);

#endif
