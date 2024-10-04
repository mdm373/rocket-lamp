#include "poll_button.h"

ButtonAction poll_button(uint16_t button_pin, uint16_t period, ButtonState* state) {
  const uint16_t prior_duration = state->duration;
  const bool was_pressed = state->was_pressed;
  const bool now_pressed = (bool)gpio_get(button_pin);
  state->was_pressed = now_pressed;
  state->duration = prior_duration + period;
  if(state->duration > LONG_PRESS_DURATION) {
    state->duration = LONG_PRESS_DURATION;
  }
  const bool down_this_frame = now_pressed && !was_pressed;
  const bool up_this_frame = !now_pressed && was_pressed;
  if(down_this_frame || up_this_frame) {
    state->duration = 0;
  }
  if(down_this_frame) {
    return BUTTON_ACTION_PRESS_DOWN;
  }
  if(now_pressed && prior_duration < LONG_PRESS_DURATION && state->duration >= LONG_PRESS_DURATION) {
    return BUTTON_ACTION_PRESS_LONG_DOWN;
  }
  if(up_this_frame && prior_duration >= LONG_PRESS_DURATION) {
    return BUTTON_ACTION_PRESS_LONG_UP;
  }
  if(up_this_frame) {
    return BUTTON_ACTION_PRESS_UP;
  }
  if(now_pressed && prior_duration >= LONG_PRESS_DURATION) {
    return BUTTON_ACTION_PRESS_LONG_HOLD;
  }
  if(now_pressed) {
    return  BUTTON_ACTION_PRESS_HOLD;
  }
  return BUTTON_ACTION_NONE;
}