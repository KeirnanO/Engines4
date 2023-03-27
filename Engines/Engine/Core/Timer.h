#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include <chrono>

constexpr float MILLI_TO_SEC = 1000.0f;

class Timer
{
public:
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;
	Timer();
	~Timer();
	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTickMilli() const;
	float GetCurrentTickSec() const;

	float timeScale = 1.0f;
private:
	unsigned int prevTicks;
	unsigned int currentTicks;

	std::chrono::high_resolution_clock::time_point prevTime;
	std::chrono::high_resolution_clock::time_point currentTime;
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;
};



#endif
