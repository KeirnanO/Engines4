#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	std::cout << "start scene" << std::endl;
	return true;
}

void StartScene::Update(const float deltaTime_)
{
	Engine::GetInstance()->SetCurrentScene(1);
}

void StartScene::Render()
{
}
