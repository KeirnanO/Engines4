#include "Engine.h"

std::unique_ptr<Engine> Engine::engineInstance = nullptr;

Engine::Engine() :window(nullptr), isRunning(false){}

Engine::~Engine() {
}

Engine* Engine::GetInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new Engine);
	}
	return engineInstance.get();
}

bool Engine::OnCreate(std::string name_, int width_, int height_) {
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		std::cout << "Window failed to initialize" << std::endl;
		OnDestroy();
		return isRunning = false;
	}

	return isRunning = true;
}

void Engine::Run() {
	while (isRunning) {
		Update(0.016f);
		Render();
	}
	if (!isRunning) {
		OnDestroy();
	}
}

bool Engine::GetIsRunning() {
	return isRunning;
}

void Engine::Update(const float deltaTime_) {

}

void Engine::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Call Game Render HERE
	SDL_GL_SwapWindow(window->GetWindow());
}

void Engine::OnDestroy() {
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}