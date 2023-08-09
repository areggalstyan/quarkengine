cmake_minimum_required(VERSION 3.19)
project(quarkengine C)

set(CMAKE_C_STANDARD 99)

add_executable(quarkengine main.c vec3.c vec3.h vec4.c vec4.h mat3.c mat3.h mat4.c mat4.h shape.c shape.h shader.c shader.h material.c material.h prefab.c prefab.h object.c object.h camera.c camera.h scene.c scene.h window.c window.h directional_light.c directional_light.h point_light.c point_light.h spotlight.c spotlight.h)
target_link_libraries(quarkengine m glad glfw dl)