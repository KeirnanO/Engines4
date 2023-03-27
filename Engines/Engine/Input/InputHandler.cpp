#include "InputHandler.h"
#include"../Core/Engine.h"

std::unique_ptr<InputHandler> InputHandler::inputInstance = nullptr;

InputHandler::InputHandler() : controller0(nullptr) {

}

InputHandler::~InputHandler() {

}

XINPUT_STATE InputHandler::GetInputState()
{
	return controller0->GetState();
}



InputHandler* InputHandler::GetInstance() {
	if (inputInstance.get() == nullptr) {
		inputInstance.reset(new InputHandler);
	}
	return inputInstance.get();
}

bool InputHandler::Initialize() {
	controller0 = new XBoxController(0);

	if (!controller0->IsConnected()){
		SearchForControllers();
	}

	return true;
}

void InputHandler::SearchForControllers()
{
	if (controller0)
	{
		if (controller0->IsConnected())
		{
			return;
		}
		else {
			
			std::cout << "no controllers found" << std::endl;
			
			//std::this_thread::sleep_for(std::chrono::milliseconds(500));
			
			return;
			//SearchForControllers();
		}
	}
}

void InputHandler::OnDestroy() {
	delete controller0;
	controller0 = nullptr;
}

void InputHandler::Update() {

	if (!controller0)
		return;

	XINPUT_STATE xinput_state = controller0->GetState();

	//Buttons
	if (xinput_state.Gamepad.wButtons > 0) {
		switch (xinput_state.Gamepad.wButtons) {
		case XINPUT_GAMEPAD_A:
			std::cout << "XINPUT_GAMEPAD_A:\n";
			break;

		case XINPUT_GAMEPAD_B:
			std::cout << "XINPUT_GAMEPAD_B\n";
			controller0->Vibrate(0x0, 0x0);
			break;

		case XINPUT_GAMEPAD_X:
			std::cout << "XINPUT_GAMEPAD_X\n";
			controller0->Vibrate(0x0, 0xFFFF);
			break;

		case XINPUT_GAMEPAD_Y:
			std::cout << "XINPUT_GAMEPAD_Y\n";
			controller0->Vibrate(0xFFFF, 0xFFFF);
			break;

		default:
			static int count = 0;
			printf("%x %d\n", xinput_state.Gamepad.wButtons, count);
			++count;
			break;
		}

	}

	//Trigger
	if (xinput_state.Gamepad.bLeftTrigger > 0) {
		/// The trigger returns a byte
		uint8_t leftTrigger = xinput_state.Gamepad.bLeftTrigger;
		printf(" left trigger %X\n", leftTrigger);
	}

	if (xinput_state.Gamepad.bRightTrigger > 0) {
		/// The trigger returns a 8 bit byte range 0 to 255
		uint8_t rightTrigger = xinput_state.Gamepad.bRightTrigger;
		printf(" right trigger %X\n", rightTrigger);
	}

	//Sticks L - R
	int16_t deadzone = 10000;
	int16_t xAxis = xinput_state.Gamepad.sThumbLX;
	int16_t yAxis = xinput_state.Gamepad.sThumbLY;
	int16_t rxAxis = xinput_state.Gamepad.sThumbRX;
	int16_t ryAxis = xinput_state.Gamepad.sThumbRY;

	/*
	//Positive
	if (xAxis > deadzone || xAxis < -deadzone || yAxis > deadzone || yAxis < -deadzone){
		/// The thumb sticks return a signed two byte short 'short' range -32768 to 32767
		printf("LeftThumb event x:%d y:%d\n", xAxis, yAxis);

		Engine::GetInstance()->NotifyOfMouseMove2(glm::fvec2(xAxis / 32768.0f, yAxis / 32768.0f));
		
	}
	if (rxAxis > deadzone || rxAxis < -deadzone || ryAxis > deadzone || ryAxis < -deadzone) {
		/// The thumb sticks return a signed two byte short 'short' range -32768 to 32767
		printf("RightThumb event x:%d y:%d\n", rxAxis, ryAxis);

		Engine::GetInstance()->NotifyOfMouseMove(glm::fvec2(rxAxis / 32768.0f, ryAxis / 32768.0f));
	}
	*/
}