#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) 
: VAO(0), VBO(0), shaderProgram(0), modelLoc(0), viewLoc(0), projLoc(0), diffuseMapLoc(0),
viewPosition(0), lightPositionLoc(0), lightAmbientLoc(0), lightDiffuseLoc(0), lightColourLoc(0){
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0)
		subMesh.vertexList.clear();

	if (subMesh.meshIndices.size() > 0)
		subMesh.meshIndices.clear();
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_){
	glUniform1i(diffuseMapLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);
	
	///Lights Not Working
	//glUniform1f(lightAmbientLoc, camera_->GetLightSources().front()->GetAmbient());
	//glUniform1f(lightDiffuseLoc, camera_->GetLightSources().at(0)->GetDiffuse());
	//glUniform3fv(lightColourLoc, 1, glm::value_ptr(camera_->GetLightSources().at(0)->GetColor()));
	//glUniform3fv(lightPositionLoc, 1, glm::value_ptr(camera_->GetLightSources().at(0)->GetPosition()));

	//glUniform3fv(viewPosition, 1, glm::value_ptr(camera_->GetPosition()));

	//Material Locations
	glUniform1f(shininessLoc, subMesh.material.shininess);
	glUniform1f(transparencyLoc, subMesh.material.transparency);	
	glUniform3fv(ambientLoc, 1, glm::value_ptr(subMesh.material.ambient));
	glUniform3fv(diffuseLoc, 1, glm::value_ptr(subMesh.material.diffuse));
	glUniform3fv(specularLoc, 1, glm::value_ptr(subMesh.material.specular));

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	

	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST);

	for(int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers(){
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);
	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position)); //diff between 0
	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	//TEXTURE COORDINATES
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//get uniform loc
	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "projection");

	//get light loc
	viewPosition = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPositionLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightColourLoc = glGetUniformLocation(shaderProgram, "light.lightColour");

	//get material loc
	diffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	shininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	ambientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	diffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	specularLoc = glGetUniformLocation(shaderProgram, "material.specular");
}


//glEnableVertexArrayAttrib