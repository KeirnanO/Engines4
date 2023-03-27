#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <XInput.h>
#include <cstdint>

class XBoxController {
private:
    int controllerID;
    XINPUT_STATE controllerState{};
public:
    XBoxController(int playerID);
    XINPUT_STATE GetState();
    bool IsConnected();
    void Vibrate(uint16_t leftValue, uint16_t rightValue);
};

#endif