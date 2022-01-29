#version 450 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TexCoords;

out VS_OUT
{
	vec3  Color;
	vec2  TexCoords;
	float Time;
} vs_out;

uniform mat4  u_ViewProjection;
uniform vec2  u_Resolution;
uniform float u_Time;

void main() {
	
	vs_out.Color = a_Color;
	vs_out.TexCoords = a_TexCoords;
	vs_out.Time = u_Time;

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
}
