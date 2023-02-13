#version 330 core
layout(location = 0) out vec4 color;
in vec4 v_Position;
in vec4 v_Color;
uniform vec4 RGBA_Colour;
void main()
{
    color = RGBA_Colour;
}
