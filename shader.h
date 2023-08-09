#ifndef QUARKENGINE_SHADER_H
#define QUARKENGINE_SHADER_H

#include "mat4.h"

typedef struct {
    unsigned int program;
} Shader;

Shader *shader_new(char *vertex, char *fragment);
void shader_delete(Shader *self);
void shader_use(Shader *self);
void shader_set_uniform_mat4(Shader *self, char *name, Mat4 value);
void shader_set_uniform_vec4(Shader *self, char *name, Vec4 value);
void shader_set_uniform_float(Shader *self, char *name, float value);
void shader_set_uniform_int(Shader *self, char *name, int value);

#endif
