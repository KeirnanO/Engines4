#version 450 core

out vec4 fColour;
uniform vec3 tintColour;

void main(){
	fColour = vec4(tintColour, 1.0f);
}