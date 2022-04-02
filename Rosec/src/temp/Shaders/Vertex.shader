#vertex
#version 410 core

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 color;

out vec4 v_Color;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vertexPosition;
	v_Color = color;
};
