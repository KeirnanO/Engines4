#ifndef MOUSEEVENTLISTENER_H
#define MOUSEEVENTLISTENER_H

#include <SDL.h>
#include <glm/glm.hpp>

class Engine;
class MouseEventListener {
public:
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator=(const MouseEventListener&) = delete;
	MouseEventListener& operator=(MouseEventListener&&) = delete;

	MouseEventListener() = delete;
	~MouseEventListener();

	static void RegisterEngineObject(Engine* engine_);
	static void Update(SDL_Event e_);

	static void NotifyOfMousePressed(int buttonType_);
	static void NotifyOfMouseReleased(int buttonType_);
	static void NotifyOfMouseMove();
	static void NotifyOfMouseScroll(int y_);

	static glm::ivec2 GetPreviousMousePosition();
	static glm::ivec2 GetMousePosition();
	static glm::ivec2 GetMouseOffset();
private:
	static Engine* engineInstance;
	static glm::ivec2 mouse, prevMouse;
	static bool firstUpdate;
	static void UpdateMousePosition();
};


#endif // !MOUSEEVENTLISTENER_H