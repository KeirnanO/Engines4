#include "Game1.h"

Game1::Game1() : GameInterface(), currentSceneNum(0), currentScene(nullptr) {
}

Game1::~Game1() {
    delete currentScene;
    currentScene = nullptr;
}

bool Game1::OnCreate(){
    if (Engine::GetInstance()->GetCurrentScene() == 0) {
        currentScene = new GameScene();
        currentSceneNum = 0;
        return currentScene->OnCreate();
    }

    Debug::Error("Engine's scene is not initatied to 0", "Game1.cpp", __LINE__);
    return false;
}

void Game1::Update(const float deltaTime_){
    if (currentSceneNum != Engine::GetInstance()->GetCurrentScene()) {
        BuildScene();
    }
    currentScene->Update(deltaTime_);
}

void Game1::Render(){
    currentScene->Render();
}

void Game1::DrawSurface() {
    currentScene->Draw();
}

void Game1::BuildScene(){
    delete currentScene;
    currentScene = nullptr;

    //All Scenes for this game will go here
    switch (Engine::GetInstance()->GetCurrentScene()) {
    case 1:
        currentScene = new GameScene();
        break;
    default: //case 0
        currentScene = new GameScene();
        break;
    }


    currentSceneNum = Engine::GetInstance()->GetCurrentScene();
    if (!currentScene->OnCreate()) {
        Debug::Error("Scene failed to be created", "Game1.cpp", __LINE__);
        Engine::GetInstance()->Exit();
    }
}
