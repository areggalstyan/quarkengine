#include <stdlib.h>
#include <stdio.h>
#include "glad/glad.h"
#include "shader.h"

static unsigned int create_shader(char *path, unsigned int type) {
    FILE *file = fopen(path, "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(size + 1);
    buffer[size] = '\0';
    fread(buffer, size, 1, file);
    fclose(file);
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, (const char **) &buffer, NULL);
    free(buffer);
    glCompileShader(shader);
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char info_log[GL_INFO_LOG_LENGTH];
        glGetShaderInfoLog(shader, GL_INFO_LOG_LENGTH, NULL, info_log);
        fputs(info_log, stderr);
    }
    return shader;
}

Shader *shader_new(char *vertex_path, char *fragment_path) {
    unsigned int vertex = create_shader(vertex_path, GL_VERTEX_SHADER);
    unsigned int fragment = create_shader(fragment_path, GL_FRAGMENT_SHADER);
    Shader *self = malloc(sizeof *self);
    self->program = glCreateProgram();
    glAttachShader(self->program, vertex);
    glAttachShader(self->program, fragment);
    glLinkProgram(self->program);
    int status;
    glGetProgramiv(self->program, GL_LINK_STATUS, &status);
    if (!status) {
        char info_log[GL_INFO_LOG_LENGTH];
        glGetShaderInfoLog(self->program, GL_INFO_LOG_LENGTH, NULL, info_log);
        fputs(info_log, stderr);
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return self;
}

void shader_delete(Shader *self) {
    free(self);
}

void shader_use(Shader *self) {
    glUseProgram(self->program);
}

void shader_set_uniform_mat4(Shader *self, char *name, Mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(self->program, name), 1, GL_TRUE, &value.m[0][0]);
}

void shader_set_uniform_vec4(Shader *self, char *name, Vec4 value) {
    glUniform4f(glGetUniformLocation(self->program, name), value.x, value.y, value.z, value.w);
}

void shader_set_uniform_float(Shader *self, char *name, float value) {
    glUniform1f(glGetUniformLocation(self->program, name), value);
}

void shader_set_uniform_int(Shader *self, char *name, int value) {
    glUniform1i(glGetUniformLocation(self->program, name), value);
}
