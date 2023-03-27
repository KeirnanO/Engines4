#ifndef INPUTHANDLER.H
#define INPUTHANDLER_H
#include <string>
#include <map>
#include <memory>
#include <thread>
#include <iostream>
#include "XBoxController.h"

class InputHandler 
{
public:
	InputHandler(const InputHandler&) = delete;
	InputHandler(InputHandler&&) = delete;
	InputHandler& operator = (const InputHandler&) = delete;
	InputHandler& operator = (const InputHandler&&) = delete;

	static InputHandler* GetInstance();

	bool Initialize();
	void OnDestroy();
	void Update();
	XINPUT_STATE GetInputState();

	~InputHandler();
private:
	InputHandler();
	

	void SearchForControllers();

	static std::unique_ptr<InputHandler> inputInstance;

	XBoxController* controller0;
};



#endif // !INPUTHANDLER.H


