#version 450 core

layout (location = 0) in vec2 a_Position;

uniform mat4 u_ViewProjection;

int main() {
  gl_Position = u_ViewProjection * vec4(a_Position, 1.0f, 1.0f);
}
