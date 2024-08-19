#ifndef INPUT_H
#define INPUT_H

#include <switch.h>
#include <switch/runtime/pad.h>  // For JoystickPosition

void processJoystickInput(JoystickPosition leftStick, JoystickPosition rightStick);

#endif // INPUT_H