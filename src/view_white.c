#include "view.h"
#include "rgb_color.h"

static uint8_t wheel_offset = 0;
static uint8_t wheel_factor = 1;
static uint8_t wheel_increment = 1;

void view_white(ButtonAction action, float scale) {
 for (int i = 0; i < NUM_PIXELS; ++i) {
    const RgbColorComps color = {.r = 255, .g = 255, .b = 255};
    rgb_color_put(comps_as_rgb_color_scaled(color, scale));
  }
}