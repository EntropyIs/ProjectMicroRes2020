#version 330 core
layout (location = 0) vec2 aPos;
layout (location = 1) vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	TexCoords = aTexCoords;
	gl_Position = projection * model * vec4(aTexCoords, 0.0f, 1.0f);
}