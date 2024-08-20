#ifndef INPUT_H
#define INPUT_H

#include <cstdint>
#include <switch.h> // Main Switch SDK header for Nintendo Switch homebrew development

struct ButtonMapping {
    uint64_t switch_button;
    uint32_t n3ds_button;

    ButtonMapping(uint64_t sb, uint32_t nb) : switch_button(sb), n3ds_button(nb) {}
};

// Function declarations
void handleInput(PadState* pad);
void processJoystickInput(HidAnalogStickState leftStick, HidAnalogStickState rightStick);
void sendButtonPressToEmulator(uint32_t n3ds_button);
void set3DSButtonState(uint32_t button, bool pressed);

#endif // INPUT_H
