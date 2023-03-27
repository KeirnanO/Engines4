#include "ImguiWindow.h"

#include "Engine.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_sdl.h"

void ImguiWindow::OnCreate()
{
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();

	auto* window = Engine::GetInstance()->GetWindow();
	ImGui_ImplSDL2_InitForOpenGL(window->GetWindow(), window->GetContext());
	ImGui_ImplOpenGL3_Init("#version 450");
	
}

void ImguiWindow::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ImguiWindow::HandleSDLEvenet(SDL_Event& e)
{
	ImGui_ImplSDL2_ProcessEvent(&e);
}

void ImguiWindow::BeginRenderer()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(Engine::GetInstance()->GetWindow()->GetWindow());
	ImGui::NewFrame();
}

void ImguiWindow::EndRenderer()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
