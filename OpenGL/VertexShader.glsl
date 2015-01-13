#version 140 core

in vec3 in_position;
in vec4 in_color;
out vec4 color;

void main() {
   color = in_color;
   gl_Position = vec4(in_position, 1.0);
}