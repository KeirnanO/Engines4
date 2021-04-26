#include "MouseEventListener.h"
#include "../Core/Engine.h"

Engine* MouseEventListener::engineInstance = nullptr;
glm::ivec2 MouseEventListener::mouse = glm::ivec2();
glm::ivec2 MouseEventListener::prevMouse = glm::ivec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener() {
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(Engine* engine_) {
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e_) {
	switch (e_.type) {
	case SDL_MOUSEBUTTONDOWN:
		UpdateMousePosition();
		NotifyOfMousePressed(e_.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		UpdateMousePosition();
		NotifyOfMouseReleased(e_.button.button);
		break;
	case SDL_MOUSEMOTION:
		UpdateMousePosition();
		NotifyOfMouseMove();
		break;
	case SDL_MOUSEWHEEL:
		UpdateMousePosition();
		NotifyOfMouseScroll(e_.wheel.y);
		break;
	default:
		break;
	}
}

void MouseEventListener::NotifyOfMousePressed(int buttonType_) {
	if (engineInstance)
		engineInstance->NotifyOfMousePressed(mouse, buttonType_);
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType_) {
	if (engineInstance)
		engineInstance->NotifyOfMouseReleased(mouse, buttonType_);
}

void MouseEventListener::NotifyOfMouseMove() {
	if (engineInstance)
		engineInstance->NotifyOfMouseMove(mouse);
}

void MouseEventListener::NotifyOfMouseScroll(int y_) {
	if (engineInstance)
		engineInstance->NotifyOfMouseScroll(y_);
}

glm::ivec2 MouseEventListener::GetPreviousMousePosition() {
	return prevMouse;
}

glm::ivec2 MouseEventListener::GetMousePosition() {
	return mouse;
}

glm::ivec2 MouseEventListener::GetMouseOffset() {
	return glm::ivec2(mouse.x - prevMouse.x, prevMouse.y - mouse.y);
}

void MouseEventListener::UpdateMousePosition() {
	int tempX, tempY;
	SDL_GetMouseState(&tempX, &tempY);
	tempY = static_cast<int>(engineInstance->GetScreenHeight()) - tempY;

	if (firstUpdate) {
		prevMouse.x = mouse.x = tempX;
		prevMouse.y = mouse.y = tempY;
		firstUpdate = false;
	}
	else {
		prevMouse.x = mouse.x;
		prevMouse.y = mouse.y;
		mouse.x = tempX;
		mouse.y = tempY;
	}
}
