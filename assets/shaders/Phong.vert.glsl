#version 330

uniform mat4x4 mat_projViewModel;

attribute vec3 v_coord;
attribute vec3 v_normal;
attribute vec2 v_texcoord;

out vec3 p_normal;
out vec2 p_texcoord;

void main() {
    gl_Position = mat_projViewModel * vec4(v_coord, 1.0f);
    p_normal = (mat_projViewModel * vec4(v_normal, 0.0f)).xyz;
    p_texcoord = v_texcoord;
}
