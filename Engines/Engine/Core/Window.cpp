#include "Window.h"
#include "Debug.h"

#include "../imgui/imgui.h"
#include "Engine.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyEvent.h"

Window::Window() : window(nullptr), context(nullptr){
	height = 800;
	width = 600;
}

Window::~Window() {
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Debug::Error("Failed to initializze SDL", "Window.cpp", __LINE__);
		return false;
	}

	width = width_;
	height = height_;

	SetPreAttributes();

	//Creater window
	window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if(!window) {
		Debug::Error("Failed to create window", "Window.cpp", __LINE__);
		return false;
	}

	context = SDL_GL_CreateContext(window);
	SetPostAttributes();

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		Debug::Error("Failed to initalize GLEW", "Window.cpp", __LINE__);
		return false;
	}

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	glViewport(0, 0, width, height);

	imguiWindow.OnCreate();

	return true;

}

void Window::OnDestroy() {

	imguiWindow.Shutdown();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth() const {
	return width;
}

int Window::GetHeight() const {
	return height;
}

SDL_Window* Window::GetWindow() const {
	return window;
}

SDL_GLContext Window::GetContext() const
{
	return context;
}

void Window::BeginRenderer()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::EndRenderer()
{
	imguiWindow.BeginRenderer();


	//Temp ImGui Layout - should have it's own layer on the stack
	{
		glm::vec3 v = Engine::GetInstance()->GetCamera()->GetPosition();
		glm::vec2 rot = { 0,0 };

		ImGui::Begin("GUI");
		ImGui::Text("Hey Engine");
		ImGui::SliderFloat("Camera Pos X", &v.x, 0.0f, 100.0f);
		ImGui::SliderFloat("Camera Pos Y", &v.y, 0.0f, 100.0f);
		ImGui::SliderFloat("Camera Pos Z", &v.z, 0.0f, 100.0f);
		ImGui::SliderFloat("Camera Yaw", &rot.x, 0.0f, 100.0f);
		ImGui::SliderFloat("Camera Pitch", &rot.y, 0.0f, 100.0f);
		//ImGui::SliderFloat3("Translate", NULL, 0.0f, 100.0f);

		std::stringstream ss;
		ss << "FPS: " << 1/Engine::GetInstance()->GetTime()->GetDeltaTime();
		ImGui::Text(ss.str().c_str());

		ss.str(std::string());
		ss << "Total Memory Allocated: " << Engine::GetInstance()->GetAllocatedMemory();
		ImGui::Text(ss.str().c_str());
		ImGui::End();

		Engine::GetInstance()->GetCamera()->SetPosition(v);
		Engine::GetInstance()->GetCamera()->SetRotation(rot.x, rot.y);
	}

	Engine::GetInstance()->OnImGuiRender();

	imguiWindow.EndRenderer();

	SDL_GL_SwapWindow(window);

	
}

void Window::PumpEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			Engine::GetInstance()->Exit();
		}
		switch (e.type) {
		case SDL_MOUSEBUTTONDOWN: {
			MouseButtonPressedEvent event(e.button.button);
			Engine::GetInstance()->OnEvent(event);
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			MouseButtonReleasedEvent event(e.button.button);
			Engine::GetInstance()->OnEvent(event);
			break;
		}
		case SDL_MOUSEMOTION: {
			int tempX, tempY;
			SDL_GetMouseState(&tempX, &tempY);

			MouseMovedEvent event(e.motion.x, e.motion.y);
			Engine::GetInstance()->OnEvent(event);
			break;
		}
		case SDL_MOUSEWHEEL: {

			MouseScrolledEvent event(e.wheel.x, e.wheel.y);
			Engine::GetInstance()->OnEvent(event);
			break;
		}
		case SDL_WINDOWEVENT_RESIZED:
			break;
		default:
			break;
		}

		imguiWindow.HandleSDLEvenet(e);
	}

			
}

void Window::SetPreAttributes() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}

void Window::SetPostAttributes() {
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}

