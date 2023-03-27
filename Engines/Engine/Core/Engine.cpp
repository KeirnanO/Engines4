#include "Engine.h"
//#include "MemoryManager.h"
#include "imgui.h"

//Temporary Profiler
template <typename Fn>
class ProfileTimer {
public:
	ProfileTimer(const char* name, Fn& func) : m_Name(name), m_Func(func), m_Stopped(false) {
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~ProfileTimer() {
		if (!m_Stopped)
			Stop();
	}

	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		//Convert to microseconds for accuracy
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		//Convert to milliseconds
		float duration = (end - start) * 0.001f;

		//std::cout << m_Name <<  " Duration: " << duration << "ms" << std::endl;
		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

//Memory Allocations 
std::size_t Engine::s_MemoryAllocated = 0; //- could be getter / setter but public for now

void* operator new(std::size_t amount, const char* file, int line) {	
	Engine::s_MemoryAllocated += amount;
	//return MemoryManager::GetInstance()->allocate(amount);
	std::cout << "allocating " << amount << " bytes of memory on line: " << line << "\n" << Engine::s_MemoryAllocated << " total memory allocated\n\n";
	return malloc(amount);
}

void operator delete(void* memoryLocation, std::size_t amount) {
	Engine::s_MemoryAllocated -= amount;
	std::cout << "freeing " << amount << " bytes of memory\n" << Engine::s_MemoryAllocated << " total memory allocated\n\n";
	free(memoryLocation);
}

#define new new(__FILE__, __LINE__)
//#define delete delete(__FILE__, __LINE__)

//Engine
std::unique_ptr<Engine> Engine::instance = nullptr;

Engine::Engine() :window(nullptr), isRunning(false), fps(60), gameInterface(nullptr), camera(nullptr), timer(nullptr), currentScene(0) {}

Engine::~Engine() {
}

Engine* Engine::GetInstance() {
	if (instance.get() == nullptr) {
		instance.reset(new Engine);
	}
	return instance.get();
}


bool Engine::OnCreate(std::string name_, int width_, int height_) {
	//Init Debug Manager
	Debug::OnCreate();

	//Create the Window
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize", "Engine.cpp", __LINE__);
		OnDestroy();
		return isRunning = false;
	}


	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);

	//Renderer::GetInstance()->SetRendererType(RendererType::OpenGL);
	//window = Renderer::GetInstance()->CreateWindow();

	//MouseEventListener::RegisterEngineObject(this);

	//Creating the basic shaderprograms
	//ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("basicShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("GUIShader", "Engine/Shaders/SpriteVertShader.glsl", "Engine/Shaders/SpriteFragShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("ParticleShader", "Engine/Shaders/ParticleVertexShader.glsl", "Engine/Shaders/ParticleFragShader.glsl");

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::FatalError("Game failed to initialize", "Engine.cpp", __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}

	Debug::Info("Engine Created Successfully!", "Engine.cpp", __LINE__);

	timer = new Timer();
	timer->Start();

	return isRunning = true;
}

void Engine::Run() {
	while (isRunning)
	{
		//ProfileTimer ptimer("Main Loop");
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint = std::chrono::high_resolution_clock::now();

		timer->UpdateFrameTicks();

		//EventListener::Update();
		Update(timer->GetDeltaTime());

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();

		Render();

		window->PumpEvents();



		SDL_Delay(timer->GetSleepTime(fps));

		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		//Convert to milliseconds
		float duration = (end - start) * 0.001f;

		m_ProfileResults.push_back({ "Main", duration });
	}

	//Destroy once not running
	OnDestroy();

}

void Engine::Update(const float deltaTime_) {
	//ProfileTimer<void> ptimer("Update", [&](ProfileResult& profileResult) { m_ProfileResults.push_back(profileResult); });

	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint = std::chrono::high_resolution_clock::now();
	
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}	

	auto endTimepoint = std::chrono::high_resolution_clock::now();

	long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
	long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

	//Convert to milliseconds
	float duration = (end - start) * 0.001f;

	m_ProfileResults.push_back({ "Update", duration });
}

void Engine::Render() {
	//ProfileTimer timer("Render");

	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint = std::chrono::high_resolution_clock::now();


	window->BeginRenderer();

	if (gameInterface) {
		gameInterface->Render();
		gameInterface->DrawSurface();
	}

	window->EndRenderer();

	auto endTimepoint = std::chrono::high_resolution_clock::now();

	long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
	long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

	//Convert to milliseconds
	float duration = (end - start) * 0.001f;

	m_ProfileResults.push_back({ "Render", duration });
}

void Engine::OnImGuiRender() {
	ImGui::Begin("Profiler");

	for (auto& result : m_ProfileResults) {
		char profileLabel[50];
		strcpy_s(profileLabel, result.name);
		strcat_s(profileLabel, " %.3fms");
		ImGui::Text(profileLabel, result.time);
	}

	m_ProfileResults.clear();

	ImGui::End();
}

void Engine::Exit() {
	isRunning = false;
}

void Engine::OnDestroy() {

	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();
	CollisionHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();

	delete gameInterface;
	gameInterface = nullptr;

	delete camera;
	camera = nullptr;

	delete timer;
	timer = nullptr;

	delete window;
	window = nullptr;

	SDL_Quit();

	std::cout << s_MemoryAllocated << " bytes left\n";
	exit(0);
}

bool Engine::GetIsRunning() const {
	return isRunning;
}

int Engine::GetCurrentScene() const {
	return  currentScene;
}

float Engine::GetScreenWidth() const {
	return static_cast<float>(window->GetWidth());
}

float Engine::GetScreenHeight() const {
	return static_cast<float>(window->GetHeight());
}

Camera* Engine::GetCamera() const {
	return camera;
}

Window* Engine::GetWindow() const {
	return window;
}

Timer* Engine::GetTime() const
{
	return timer;
}

void Engine::SetGameInterface(GameInterface * gameInterface_) {
	gameInterface = gameInterface_;
}

void Engine::SetCurrentScene(int sceneNum_) {
	currentScene = sceneNum_;
}

void Engine::SetCamera(Camera * camera_) {
	camera = camera_;
}

void Engine::OnEvent(Event & e)
{
	//std::cout << e.ToString() << std::endl;
	EventDispatcher dispatcher(e);

	for (auto i = m_LayerStack.end(); i != m_LayerStack.begin();)
	{
		(*--i)->OnEvent(e);
		//if (e.Handled);
			//break;
	}


}

void Engine::PushLayer(Layer * layer)
{
	m_LayerStack.PushLayer(layer);
}

/*
void Engine::NotifyOfMousePressed(glm::ivec2 mouse_, int buttonType_) {
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void Engine::NotifyOfMouseReleased(glm::ivec2 mouse_, int buttonType_) {
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void Engine::NotifyOfMouseMove(glm::vec2 mouse_) {

	float sensitivity = 5.0f;
	mouse_ *= sensitivity;

	if (camera) {
		std::cout << mouse_.x << ", " << mouse_.y;

		camera->ProcessRotMovement(mouse_);
	}
}

void Engine::NotifyOfMouseMove2(glm::vec2 mouse_) {


	if (camera) {
		std::cout << mouse_.x << ", " << mouse_.y;

		glm::vec3 right = glm::cross(camera->GetForward(), camera->GetUp());
		glm::vec3 movement = (right * mouse_.x) + (camera->GetForward() * mouse_.y);

		camera->SetPosition(camera->GetPosition() + movement);
	}
}

void Engine::NotifyOfMouseScroll(int y_) {
	if (camera) {
		camera->ProcessMouseZoom(y_);
	}
}*/


