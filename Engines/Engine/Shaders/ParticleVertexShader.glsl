#version 450 core

layout (location = 0) in vec3 position;
layout (location = 3) in vec3 colour;



out vec3 Colour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float Size;

void main(){
	gl_Position = proj * view * model * vec4(0.0f, 0.0f, 0.0f, 1.0f);
	vec4 translate = view * model * vec4(position, 1.0f);
	float distance = length(vec3(translate));
	float attenuation = inversesqrt(0.1f * distance);
	gl_PointSize = attenuation * Size;
	Colour = colour;
}