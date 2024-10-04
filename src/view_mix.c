#include <math.h>
#include "view.h"
#include "rgb_color.h"

static uint8_t rgb[3];
static uint8_t comp_index;
static float prior_scale;
static uint32_t feedback_duration;


rgb_color feedback_color() {
  if(comp_index == 0) return as_rgb_color(255, 0, 0);
  if(comp_index == 1) return as_rgb_color(0, 255, 0);
  return as_rgb_color(0, 0, 255);
}
bool view_feedback(float scale) {
  if (feedback_duration >= FEEDBACK_DELAY) {
    return false;
  }

  int max_pixel = NUM_PIXELS * scale;
  for (int i = 0; i < NUM_PIXELS; ++i) {
    if (i > max_pixel) {
      rgb_color_put(0);
      continue;
    }

    rgb_color_put(feedback_color());
  }
  feedback_duration = feedback_duration + FRAME_MS;
  if(feedback_duration > FEEDBACK_DELAY) {
    feedback_duration = FEEDBACK_DELAY;
  }
  return true;
}

void view_mix(ButtonAction action, float scale) {
  if (action > BUTTON_ACTION_PRESS_UP) {
    prior_scale = scale;
    rgb[0] = 255;
    rgb[1] = 255;
    rgb[2] = 255;
    comp_index = 0;
  }
  if (action == BUTTON_ACTION_PRESS_UP) {
    comp_index = (comp_index + 1) % 3;
    feedback_duration = 0;
  }
  if(fabs(scale - prior_scale) > .01f) {
    feedback_duration = 0;
  }
  prior_scale = scale;
  rgb[comp_index] = 255 * scale;
  if(view_feedback(scale)) return;
  

  rgb_color mixed = arr_as_rgb_color(rgb);
  for (int i = 0; i < NUM_PIXELS; ++i) {
    rgb_color_put(mixed);
  }
}