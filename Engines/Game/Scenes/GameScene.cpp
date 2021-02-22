#include "GameScene.h"

GameScene::GameScene() : shape(nullptr) {

}

GameScene::~GameScene(){
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	Debug::Info("Creating GameScene", "GameScene.cpp", __LINE__);

	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(3);
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	v.colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	v.colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	v.colour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	vertexList.push_back(v);

	Vertex v2;
	std::vector<Vertex> vertexList2;
	vertexList2.reserve(3);
	v2.position = glm::vec3(0.5f, -0.5f, 0.0f);
	v2.colour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	vertexList2.push_back(v2);
	v2.position = glm::vec3(0.5f, 0.5f, 0.0f);
	v2.colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	vertexList2.push_back(v2);
	v2.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	v2.colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	vertexList2.push_back(v2);

	Model* model = new Model(ShaderHandler::GetInstance()->GetShader("colourShader"));
	model->AddMesh(new Mesh(vertexList));
	model->AddMesh(new Mesh(vertexList2));
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_){
}

void GameScene::Render(){
	shape->Render();
}
