#ifndef ENGINE_H
#define ENGINE_H


#include "Window.h"
#include <memory>

 class Engine
{
public:	
	Engine(const Engine&) = delete;
	Engine(const Engine&&) = delete;
	Engine& operator =(const Engine&) = delete;
	Engine& operator=(Engine&&) = delete;

	static Engine* GetInstance();

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();
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
};



#endif // !ENGINE_H

