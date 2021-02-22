#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec4 colour;

out vec3 Normal;
out vec2 TexCoords;
out vec4 Colour;

void main(){
	gl_Position = vec4(position, 1.0f);
	Colour = colour;
}