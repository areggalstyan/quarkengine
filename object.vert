#version 330 core

layout (location = 0) in vec4 v_in_position;
layout (location = 1) in vec4 v_in_normal;
out vec4 v_out_position;
out vec4 v_out_normal;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    v_out_position = u_model * v_in_position;
    v_out_normal = transpose(inverse(u_model)) * vec4(v_in_normal.xyz, 0);
    gl_Position = u_projection * u_view * v_out_position;
}
