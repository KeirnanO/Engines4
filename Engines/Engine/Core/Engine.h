#ifndef ENGINE_H
#define ENGINE_H


#include "Window.h"
#include <memory>
#include "Timer.h"
#include "GameInterface.h"
#include "Scene.h"
#include "Debug.h"

#include "../Rendering/3D/GameObject.h"

#include "../Graphics/ShaderHandler.h"

 class Engine{
public:	
	Engine(const Engine&) = delete;
	Engine(const Engine&&) = delete;
	Engine& operator =(const Engine&) = delete;
	Engine& operator=(Engine&&) = delete;

	static Engine* GetInstance();

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	void Exit();
	
	bool GetIsRunning() const;
	int GetCurrentScene() const;

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_);

private:
	Engine();
	~Engine();
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static std::unique_ptr<Engine> engineInstance;
	friend std::default_delete<Engine>;

	Window* window;
	bool isRunning;
	Timer* timer;
	unsigned int fps;

	GameInterface* gameInterface;
	int currentScene; //Can be enum for more precise scene management
};



#endif // !ENGINE_H

