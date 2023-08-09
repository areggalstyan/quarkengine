#include <stdlib.h>
#include "glad/glad.h"
#include "window.h"

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window *window_new(char *title, int width, int height) {
    Window *self = malloc(sizeof *self);
    self->delta = 0;
    if (!glfwInit()) {
        return NULL;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    self->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!self->window) {
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(self->window);
    glfwSetFramebufferSizeCallback(self->window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        return NULL;
    }
    glEnable(GL_DEPTH_TEST);
    return self;
}

void window_delete(Window *self) {
    glfwTerminate();
    free(self);
}

void window_set_scene(Window *self, Scene *scene) {
    self->scene = scene;
}

bool window_is_open(Window *self) {
    return !glfwWindowShouldClose(self->window);
}

void window_draw(Window *self) {
    Vec4 forward, right, up;
    camera_get_directions(self->scene->camera, &forward, &right, &up);
    float time = (float) glfwGetTime();
    float delta = time - self->delta;
    self->delta = time;
    if (glfwGetKey(self->window, GLFW_KEY_W) == GLFW_PRESS) {
        camera_move_towards(self->scene->camera, forward, -delta);
    }
    if (glfwGetKey(self->window, GLFW_KEY_S) == GLFW_PRESS) {
        camera_move_towards(self->scene->camera, forward, delta);
    }
    if (glfwGetKey(self->window, GLFW_KEY_A) == GLFW_PRESS) {
        camera_move_towards(self->scene->camera, right, -delta);
    }
    if (glfwGetKey(self->window, GLFW_KEY_D) == GLFW_PRESS) {
        camera_move_towards(self->scene->camera, right, delta);
    }
    if (glfwGetKey(self->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera_move_towards(self->scene->camera, up, delta);
    }
    if (glfwGetKey(self->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera_move_towards(self->scene->camera, up, -delta);
    }
    if (glfwGetKey(self->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(self->window, GLFW_TRUE);
    }
    if (glfwGetMouseButton(self->window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(self->window, &x, &y);
        int width, height;
        glfwGetWindowSize(self->window, &width, &height);
        Vec4 target = vec4((float) (2 * x / width - 1), (float) (-2 * y / height + 1), 1);
        camera_look_at(self->scene->camera, target);
    }
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene_draw(self->scene);
    glfwSwapBuffers(self->window);
    glfwPollEvents();
}
