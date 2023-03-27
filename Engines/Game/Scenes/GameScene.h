#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/Engine.h"
#include "../../Engine/FX/Particle System/Emitter.h"
#include"../../Engine/Math/PhysicsSolver.h"

class GameScene : public Scene{
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() override;
	virtual void Draw();

private:
	Emitter* emitter;
	PhysicsSolver* physicsSolver;
};

#endif // !GAMESCENE_HJ