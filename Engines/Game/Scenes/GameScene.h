#ifndef GAMESCENE_HJ
#define GAMESCENE_H

#include "../../Engine/Core/Engine.h"

class GameScene : public Scene{
public:
	GameScene();
	virtual ~GameScene();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
};

#endif // !GAMESCENE_HJ