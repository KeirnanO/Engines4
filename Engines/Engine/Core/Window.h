#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>

#include "ImguiWindow.h"


class Window
{
public:
	Window();
	~Window();
	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();
	int GetWidth() const;
	int GetHeight() const;
	SDL_Window* GetWindow() const;
	SDL_GLContext GetContext() const;
	void BeginRenderer();
	void EndRenderer();
	void PumpEvents();

	SDL_Window* window;
	SDL_GLContext context;
	ImguiWindow imguiWindow;

private:
	void SetPreAttributes();
	void SetPostAttributes();

	int width;
	int height;
	

};


#endif // !WINDOW_H


