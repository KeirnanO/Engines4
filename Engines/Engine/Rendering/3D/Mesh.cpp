#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertexList_, GLuint shaderProgram_) : VAO(0), VBO(0), vertexList(std::vector<Vertex>()), shaderProgram(0), modelLoc(0), viewLoc(0), projLoc(0){
	vertexList = vertexList_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	vertexList.clear();
}

void Mesh::Render(Camera* camera_, glm::mat4 transform_){
	glBindVertexArray(VAO);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform_));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glEnable(GL_DEPTH_TEST);

	glDrawArrays(GL_TRIANGLES, 0, vertexList.size());

	glBindVertexArray(0);
}

void Mesh::GenerateBuffers(){
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);
	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position)); //diff between 0
	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	//TEXTURE COORDINATES
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));
	//COLOUR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "projection");
}


//glEnableVertexArrayAttrib