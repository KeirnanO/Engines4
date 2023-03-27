#ifndef EMITTER_H
#define EMITTER_H

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include <string>
#include "../../Graphics/ShaderHandler.h"
#include "../../Graphics/TextureHandler.h"
#include "Particle.h"
#include <cstdlib>

class Emitter
{
public:
	Emitter(int particles_, std::string shaderProgram_);
	~Emitter();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

	void ParticleLife(Particle* particle_);
	const std::string particleVertexShaderName, particleFragmentShaderName;

private:
	std::vector<Particle*> particles;
	int particleCount;
	std::string particleTexture;
	const std::string particleShaderProgramName;
	GLuint particleShader, textureID;
};
#endif
