#include <iostream>
#include "XBoxController.h"

XBoxController::XBoxController(int playerID) : controllerID(playerID) {
    memset(&controllerState, 0, sizeof(controllerState));
}

XINPUT_STATE XBoxController::GetState() {
    XInputGetState(controllerID, &controllerState);
    return controllerState;
}

bool XBoxController::IsConnected() {
    uint16_t result = XInputGetState(controllerID, &controllerState);
    if (result == ERROR_SUCCESS) {
        return true;
    }
    std::cerr << "No controller " << controllerID << " found\n";
    return false;

}

void XBoxController::Vibrate(uint16_t leftValue, uint16_t rightValue) {
    XINPUT_VIBRATION vibration{};
    vibration.wLeftMotorSpeed = leftValue;
    vibration.wRightMotorSpeed = rightValue;
    XInputSetState(controllerID, &vibration);
}