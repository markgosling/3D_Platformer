#version 130

out vec4 out_color;

uniform float red;
uniform float green;
uniform float blue;

vec4 shape_color = vec4(red, green, blue, 1.0f);

void main()
{
        out_color = shape_color;
}