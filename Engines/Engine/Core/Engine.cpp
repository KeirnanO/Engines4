#include "Engine.h"


std::unique_ptr<Engine> Engine::instance = nullptr;

Engine::Engine() :window(nullptr), isRunning(false), fps(60), gameInterface(nullptr), camera(nullptr), timer(nullptr), currentScene(0){}

Engine::~Engine() {
}

Engine* Engine::GetInstance() {
	if (instance.get() == nullptr) {
		instance.reset(new Engine);
	}
	return instance.get();
}

bool Engine::OnCreate(std::string name_, int width_, int height_) {
	Debug::OnCreate();
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize", "Engine.cpp", __LINE__);
		OnDestroy();
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	//ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("basicShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");

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
	while (isRunning) {
		timer->UpdateFrameTicks();
		EventListener::Update();
		Update(timer->GetDeltaTime());
		Render();
		SDL_Delay(timer->GetSleepTime(fps));
	}

	//Destroy once not running
	OnDestroy();

}

void Engine::Exit(){
	isRunning = false;
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

void Engine::SetGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}

void Engine::SetCurrentScene(int sceneNum_){
	currentScene = sceneNum_;
}

void Engine::SetCamera(Camera* camera_){
	camera = camera_;
}

void Engine::NotifyOfMousePressed(glm::ivec2 mouse_, int buttonType_){
}

void Engine::NotifyOfMouseReleased(glm::ivec2 mouse_, int buttonType_){
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

//Why is mouse_ needed here
void Engine::NotifyOfMouseMove(glm::ivec2 mouse_){
	if (camera) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void Engine::NotifyOfMouseScroll(int y_){
	if (camera) {
		camera->ProcessMouseZoom(y_);
	}
}

void Engine::Update(const float deltaTime_) {
	if (gameInterface) {
		gameInterface-> Update(deltaTime_);
		//std::cout << deltaTime_ << std::endl;
	}
}

void Engine::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameInterface) {
		gameInterface->Render();
	}

	SDL_GL_SwapWindow(window->GetWindow());
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
	exit(0);
}