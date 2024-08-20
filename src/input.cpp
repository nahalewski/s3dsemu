#include "input.h"
#include <switch/runtime/devices/console.h>  // Ensure this is the correct header for console-specific functions

ButtonMapping mappings[12] = {
    {HidNpadButton_A, 0x0001},     // Switch A -> 3DS A
    {HidNpadButton_B, 0x0002},     // Switch B -> 3DS B
    {HidNpadButton_X, 0x0008},     // Switch X -> 3DS X
    {HidNpadButton_Y, 0x0004},     // Switch Y -> 3DS Y
    {HidNpadButton_L, 0x0040},     // Switch L -> 3DS L
    {HidNpadButton_R, 0x0080},     // Switch R -> 3DS R
    {HidNpadButton_ZL, 0x0800},    // Switch ZL -> 3DS ZL
    {HidNpadButton_ZR, 0x1000},    // Switch ZR -> 3DS ZR
    {HidNpadButton_Plus, 0x0200},  // Switch Start -> 3DS Start
    {HidNpadButton_Minus, 0x0100}, // Switch Select -> 3DS Select
    {HiddbgNpadButton_Home, 0x0400},  // Switch Home -> 3DS Home
    {HidNpadButton_StickL, 0x2000} // Switch Left Joystick Button -> 3DS Left Joystick Click
};

void handleInput(PadState* pad) {
    padUpdate(pad);
    u64 kDown = padGetButtonsDown(pad);
    u64 kHeld = padGetButtons(pad);  
    (void)kHeld;  // Suppress warning for unused variable

    for (int i = 0; i < 12; ++i) {
        if (kDown & mappings[i].switch_button) {
            sendButtonPressToEmulator(mappings[i].n3ds_button);
        }
    }

    HidAnalogStickState leftStick = padGetStickPos(pad, 0);
    HidAnalogStickState rightStick = padGetStickPos(pad, 1);

    processJoystickInput(leftStick, rightStick);
}

void processJoystickInput(HidAnalogStickState leftStick, HidAnalogStickState rightStick) {
    int left_x = leftStick.x;
    int left_y = leftStick.y;
    int right_x = rightStick.x;
    int right_y = rightStick.y;

    // Suppress warnings for unused variables
    (void)left_x;
    (void)left_y;
    (void)right_x;
    (void)right_y;

    // Apply this input to your emulator logic (add your logic here if needed)
}

void sendButtonPressToEmulator(uint32_t n3ds_button) {
    set3DSButtonState(n3ds_button, true);
}

void set3DSButtonState(uint32_t button, bool pressed) {
    // Implement your emulator's input handling logic here
}
