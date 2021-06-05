#version 450 core 

in vec3 o_Color;
in float o_Time;
out vec3 color;

void main()
{
	color = vec3(
    abs(sin(o_Color.r * o_Time)),
    abs(cos(o_Color.g * o_Time)),
    abs(sin(o_Color * o_Time))
  );
}
