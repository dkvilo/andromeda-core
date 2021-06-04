#version 450 core

layout (location = 0) out vec3 o_Color;

uniform vec3 u_Color;

void main()
{
	o_Color = u_Color;
}