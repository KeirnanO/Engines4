#ifndef SPRITESURFACE_H
#define SPRITESURFACE_H

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "../../Camera/Camera.h"
#include "../../Graphics/TextureHandler.h"

struct Vertex2D {
	glm::vec2 spritePosition;
	glm::vec2 spriteTextureCoords;
	Vertex2D(glm::vec2 position_, glm::vec2 texturecoords_) {
		spritePosition = position_;
		spriteTextureCoords = texturecoords_;
	};
};

class SpriteSurface
{
public:
	SpriteSurface(std::string imageLoader_, glm::vec2 imageScaler_, float angle_, glm::vec4 tintColour_);
	~SpriteSurface();

	void DrawSurface(Camera* camera_, glm::vec2 position_);

	float GetWidth(), GetHeight();


private:
	GLuint VAO, VBO, modelLoc, projLoc, colourLoc, textureLoc, viewLoc;
	GLuint textureID = 0;
	GLuint spriteShaderProgram;
	std::string imageLoader;
	float angle, width, height;
	glm::vec4 tintColour;
	glm::vec2 imageScaler, position;
	std::vector<Vertex2D> vertexList;
	void GenerateBuffers();
};

#endif