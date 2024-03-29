#include "Timer.h"

Timer::Timer() : prevTicks(0), currentTicks(0) {}

Timer::~Timer() {}

void Timer::Start() {
	prevTicks = currentTicks = SDL_GetTicks();

	prevTime = currentTime = startTime = std::chrono::high_resolution_clock::now();
}

void Timer::UpdateFrameTicks() {
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();

	prevTime = currentTime;

	currentTime = std::chrono::high_resolution_clock::now();
}

float Timer::GetDeltaTime() const{
	return (currentTicks - prevTicks) / MILLI_TO_SEC * timeScale;
}

unsigned int Timer::GetSleepTime(const unsigned int fps) const {
	unsigned int milliSecsPerSec = MILLI_TO_SEC / fps;
	if (milliSecsPerSec == 0) {
		return 0;
	}
	unsigned int sleepTime = milliSecsPerSec - (SDL_GetTicks() - currentTicks); //*
	if (sleepTime > milliSecsPerSec) {
		return milliSecsPerSec;
	}
	return sleepTime;
}

float Timer::GetCurrentTickMilli() const{
	return static_cast<float>(currentTicks); //*
}

float Timer::GetCurrentTickSec() const {
	return currentTicks / MILLI_TO_SEC;
}
