#include "view.h"
#include "rgb_color.h"

static uint8_t wheel_offset = 0;
static uint8_t wheel_factor = 1;
static uint8_t wheel_increment = 1;

void view_rainbow(ButtonAction action, float scale) {
  if (action > BUTTON_ACTION_PRESS_UP) {
    wheel_factor = 1;
    wheel_increment = 1;
    wheel_offset = 0;
    if (NUM_PIXELS < 255) {
      wheel_factor = 255 / NUM_PIXELS;
    }
  }
  if (action == BUTTON_ACTION_PRESS_UP) {
    wheel_increment = (wheel_increment + 3) % 12;
  }
  for (int i = 0; i < NUM_PIXELS; ++i) {
    const RgbColorComps color = wheel_color(((i * wheel_factor) + wheel_offset) % 255);
    rgb_color_put(comps_as_rgb_color_scaled(color, scale));
  }
  wheel_offset = (wheel_offset + wheel_increment) % 255;
}