  
#version 450 core 
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 Normal;
out vec2 TexCoords;
out vec3 Colour;
out vec3 FragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	gl_Position = proj * view * model * vec4(position, 1.0f);
	Normal = vec3(transpose(inverse(model)) * vec4(normal.x, normal.y, normal.z, 0.0));
	FragPosition = vec3(model*vec4(position.x, position.y, position.z, 0.0));
	TexCoords = texCoords;
	Colour = vec3(1.0f);

}