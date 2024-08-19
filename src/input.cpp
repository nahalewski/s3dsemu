#include "input.h"
#include <switch/runtime/devices/console.h>  // For gfxInitDefault and gfxExit

ButtonMapping mappings[12];  // Now 12 buttons

void initializeDefaultMappings() {
    mappings[0] = {KEY_A, 0x0001};     // Switch A -> 3DS A
    mappings[1] = {KEY_B, 0x0002};     // Switch B -> 3DS B
    mappings[2] = {KEY_X, 0x0008};     // Switch X -> 3DS X
    mappings[3] = {KEY_Y, 0x0004};     // Switch Y -> 3DS Y
    mappings[4] = {KEY_L, 0x0040};     // Switch L -> 3DS L
    mappings[5] = {KEY_R, 0x0080};     // Switch R -> 3DS R
    mappings[6] = {KEY_ZL, 0x0800};    // Switch ZL -> 3DS ZL
    mappings[7] = {KEY_ZR, 0x1000};    // Switch ZR -> 3DS ZR
    mappings[8] = {KEY_PLUS, 0x0200};  // Switch Start -> 3DS Start
    mappings[9] = {KEY_MINUS, 0x0100}; // Switch Select -> 3DS Select
    mappings[10] = {KEY_HOME, 0x0400}; // Switch Home -> 3DS Home
    mappings[11] = {KEY_LSTICK, 0x2000}; // Switch Left Joystick Button -> 3DS Left Joystick Click
}

void handleInput() {
    hidScanInput();
    u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
    u64 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);

    for (int i = 0; i < 12; ++i) {
        if (kDown & mappings[i].switch_button) {
            sendButtonPressToEmulator(mappings[i].n3ds_button);
        }
    }

    JoystickPosition leftStick, rightStick;
    hidJoystickRead(&leftStick, CONTROLLER_P1_AUTO, JOYSTICK_LEFT);
    hidJoystickRead(&rightStick, CONTROLLER_P1_AUTO, JOYSTICK_RIGHT);

    processJoystickInput(leftStick, rightStick);
}

void processJoystickInput(JoystickPosition leftStick, JoystickPosition rightStick) {
    // Translate joystick positions into 3DS analog input values
    int left_x = leftStick.dx;
    int left_y = leftStick.dy;
    int right_x = rightStick.dx;
    int right_y = rightStick.dy;

    // Apply this input to your emulator logic
}

void sendButtonPressToEmulator(uint32_t n3ds_button) {
    // Here you would set the corresponding bit in your emulator's input state
    set3DSButtonState(n3ds_button, true);
}

void set3DSButtonState(uint32_t button, bool pressed) {
    // Integrate this with your emulator's input handling system
}