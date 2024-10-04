#ifndef POLL_BUTTON_INCLUDE
#define POLL_BUTTON_INCLUDE

#include "hardware/gpio.h"
#include "stdbool.h"

#define BUTTON_ACTION_PRESS_LONG_UP 0x06
#define BUTTON_ACTION_PRESS_LONG_HOLD 0x05
#define BUTTON_ACTION_PRESS_LONG_DOWN 0x04
#define BUTTON_ACTION_PRESS_UP 0x03
#define BUTTON_ACTION_PRESS_HOLD 0x02
#define BUTTON_ACTION_PRESS_DOWN 0x01
#define BUTTON_ACTION_NONE 0x00

#define LONG_PRESS_DURATION 750

typedef struct ButtonState_T {
  bool was_pressed;
  uint16_t duration;
} ButtonState;

typedef uint8_t ButtonAction;

ButtonAction poll_button(uint16_t button_pin, uint16_t period, ButtonState* state);

#endif
