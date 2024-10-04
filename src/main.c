#include <stdlib.h>

#include "poll_button.h"
#include "read_adc.h"
#include "rgb_color.h"
#include "view.h"

int main() {
  read_adc_init(ADC_PIN);
  rgb_color_init(WS2812_PIN, IS_RGBW);
  View views[] = {&view_rainbow, &view_rocket, &view_white, &view_mix};
  uint8_t view_count = sizeof(views) / sizeof(views[0]);
  ButtonState button_state;
  uint8_t view_index = 0;
  views[view_index](BUTTON_ACTION_PRESS_LONG_DOWN, 1.0f);
  sleep_ms(FRAME_MS);
  while (1) {
    const ButtonAction button_action = poll_button(BUTTON_PIN, FRAME_MS, &button_state);
    const float scale = read_adc_percent();
    if (button_action == BUTTON_ACTION_PRESS_LONG_DOWN) {
      view_index = (view_index + 1) % view_count;
    }
    views[view_index](button_action, scale);
    sleep_ms(FRAME_MS);
  }
}
