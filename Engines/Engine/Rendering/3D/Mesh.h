#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Camera/Camera.h"
#include "../../Graphics/MaterialHandler.h"

#include "..\RenderAPI\Buffer.h"
#include "..\RenderAPI\VertexArray.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<unsigned int> meshIndices;
	Material material;
};

class Mesh{
public:
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, std::vector<glm::mat4>& instances_);

private:
	void GenerateBuffers();
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;
	GLuint VAO, VBO;
	SubMesh subMesh;
	GLuint shaderProgram;

	GLuint modelLoc, viewLoc, projLoc,
		viewPosition, lightPositionLoc, lightAmbientLoc, lightDiffuseLoc, lightColourLoc, lightSpecularLoc,
		diffuseMapLoc, shininessLoc, transparencyLoc, ambientLoc, diffuseLoc, specularLoc;
};


#endif

 