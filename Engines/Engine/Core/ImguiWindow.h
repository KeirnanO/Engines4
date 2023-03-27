#ifndef IMGUIWINDOW_H
#define IMGUIWINDOW_H


typedef union SDL_Event;
class ImguiWindow
{
public:
	ImguiWindow() {}
	~ImguiWindow() {}

	void OnCreate();
	void Shutdown();
	void HandleSDLEvenet(SDL_Event& e);

	void BeginRenderer();
	void EndRenderer();
};

#endif

