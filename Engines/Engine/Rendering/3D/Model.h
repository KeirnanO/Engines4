#ifndef MODEL_H
#define MODEL_H

#include "LoadOBJModel.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class Model
{
public:
	Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_);
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);
	unsigned int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(unsigned int index, glm::vec3 position_, float angle_, glm::vec3 rotation, glm::vec3 scale);
	glm::mat4 GetTransform(unsigned int index) const;
	GLuint GetShaderProgram() const;

private:
	glm::mat4 CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation, glm::vec3 scale) const;
	void LoadModel();

	std::vector<Mesh*> meshes;
	GLuint shaderProgram;
	std::vector<glm::mat4> modelInstances;
	LoadOBJModel* obj;
};

#endif // !MODEL_H
