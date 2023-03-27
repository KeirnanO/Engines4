#ifndef GAME1_H
#define GAME1_H

#include "../Engine/Core/Engine.h"
#include "Scenes//StartScene.h"
#include "Scenes//GameScene.h"

class Game1 : public GameInterface {
public:
	Game1();
	virtual ~Game1();

	virtual bool OnCreate() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() override;
	virtual void DrawSurface() override;

private:
	int currentSceneNum;
	Scene* currentScene;

	void BuildScene();
};


#endif // !GAME1_H