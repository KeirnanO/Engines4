#ifndef ENGINE_H
#define ENGINE_H


#include "Window.h"
#include <memory>
#include "Timer.h"
#include "GameInterface.h"
#include "Scene.h"
#include "Debug.h"
#include "Layer.h"
#include "LayerStack.h"

#include "../Camera/Camera.h"

#include "../Events/Event.h"

#include "../Rendering/SceneGraph.h"
#include "../Rendering/3D/GameObject.h"

#include "..\Rendering\RenderAPI\Renderer.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"
#include "../Graphics/MaterialHandler.h"

class Engine {
public:
	Engine(const Engine&) = delete;
	Engine(const Engine&&) = delete;
	Engine& operator=(const Engine&) = delete;
	Engine& operator=(Engine&&) = delete;

	static Engine* GetInstance();

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	void Exit();

	bool GetIsRunning() const;
	int GetCurrentScene() const;
	float GetScreenWidth() const;
	float GetScreenHeight() const;
	Camera* GetCamera() const;
	Window* GetWindow() const;
	Timer* GetTime() const;

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_);
	void SetCamera(Camera* camera);
	
	void OnEvent(Event& e);
	void OnImGuiRender();

	void PushLayer(Layer* layer);
	inline static std::size_t GetAllocatedMemory() { return s_MemoryAllocated; }
	static std::size_t s_MemoryAllocated;
	

private:
	Engine();
	~Engine();
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();


	static std::unique_ptr<Engine> instance;
	friend std::default_delete<Engine>;

	Window* window;
	bool isRunning;
	Timer* timer;
	unsigned int fps;

	GameInterface* gameInterface;
	int currentScene; //Can be enum for more precise scene management

	Camera* camera;
	
	LayerStack m_LayerStack;

	struct ProfileResult {
		const char* name;
		float time;
	};

	std::vector<ProfileResult> m_ProfileResults;
	
};

#endif // !ENGINE_H

