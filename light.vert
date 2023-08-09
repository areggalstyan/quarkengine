#version 330 core

layout (location = 0) in vec4 v_in_position;
layout (location = 1) in vec4 v_in_normal;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_view * u_model * v_in_position;
}
