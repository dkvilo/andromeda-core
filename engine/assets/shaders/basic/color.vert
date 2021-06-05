#version 450 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Color;

out vec3  o_Color;
out float o_Time;

uniform mat4  u_ViewProjection;
uniform vec2  u_Resolution;
uniform float u_Time;

vec3 position;

void main() {
  
  o_Color = a_Color;
  o_Time = u_Time;

  gl_Position = vec4(a_Position, 1.0f);
}
