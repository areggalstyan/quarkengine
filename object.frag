#version 330 core

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

struct DirectionalLight {
    vec4 direction;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct PointLight {
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float constant;
    float linear;
    float quadratic;
};

struct Spotlight {
    vec4 position;
    vec4 direction;
    float inner;
    float outer;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

in vec4 v_out_position;
in vec4 v_out_normal;
out vec4 f_out_color;
uniform vec4 u_camera;
uniform Material u_material;
uniform DirectionalLight u_directional_lights[10];
uniform int u_ndirectional_lights;
uniform PointLight u_point_lights[10];
uniform int u_npoint_lights;
uniform Spotlight u_spotlights[10];
uniform int u_nspotlights;

vec4 get_light(vec3 light_direction, vec4 light_ambient, vec4 light_diffuse, vec4 light_specular, float intensity) {
    light_direction = normalize(light_direction);
    vec4 ambient = light_ambient * u_material.ambient;
    vec3 normal = normalize(v_out_normal.xyz);
    float diffuse_intensity = max(dot(normal, light_direction), 0);
    vec4 diffuse = diffuse_intensity * light_diffuse * u_material.diffuse;
    vec3 camera_direction = normalize(u_camera.xyz - v_out_position.xyz);
    vec3 reflection_direction = reflect(-light_direction, normal);
    float specular_intensity = pow(max(dot(camera_direction, reflection_direction), 0), u_material.shininess);
    vec4 specular = specular_intensity * light_specular * u_material.specular;
    return ambient + intensity * (diffuse + specular);
}

vec4 get_directional_light(DirectionalLight light) {
    return get_light(-light.direction.xyz, light.ambient, light.diffuse, light.specular, 1);
}

vec4 get_point_light(PointLight light) {
    vec3 light_direction = light.position.xyz - v_out_position.xyz;
    float distance = length(light_direction);
    float attenuation = light.constant + light.linear * distance + light.quadratic * distance * distance;
    return get_light(light_direction, light.ambient, light.diffuse, light.specular, 1 / attenuation);
}

vec4 get_spotlight(Spotlight light) {
    vec3 light_direction = normalize(light.position.xyz - v_out_position.xyz);
    float theta = dot(light_direction, normalize(-light.direction.xyz));
    float intensity = clamp((theta - light.outer) / (light.inner - light.outer), 0, 1);
    return get_light(light_direction, light.ambient, light.diffuse, light.specular, intensity);
}

void main() {
    vec4 color = vec4(0);
    for (int i = 0; i < u_ndirectional_lights; i++) {
        color += get_directional_light(u_directional_lights[i]);
    }
    for (int i = 0; i < u_npoint_lights; i++) {
        color += get_point_light(u_point_lights[i]);
    }
    for (int i = 0; i < u_nspotlights; i++) {
        color += get_spotlight(u_spotlights[i]);
    }
    f_out_color = color;
}
