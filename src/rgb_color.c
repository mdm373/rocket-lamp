#include "rgb_color.h"

rgb_color comps_as_rgb_color(RgbColorComps comps) {
  return ((uint32_t)(comps.r) << 8) | ((uint32_t)(comps.g) << 16) |
         (uint32_t)(comps.b);
}

rgb_color arr_as_rgb_color(uint8_t arr[3]) {
  return ((uint32_t)(arr[0]) << 8) | ((uint32_t)(arr[1]) << 16) |
         (uint32_t)(arr[2]);
}

rgb_color comps_as_rgb_color_scaled(RgbColorComps comps, float scale) {
  return ((uint32_t)(comps.r * scale) << 8) |
         ((uint32_t)(comps.g * scale) << 16) | (uint32_t)(comps.b * scale);
}

rgb_color as_rgb_color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

RgbColorComps as_rgb_color_comps(uint8_t r, uint8_t g, uint8_t b) {
  return (RgbColorComps){.r = r, .g = g, .b = b};
}

RgbColorComps wheel_color(uint8_t pos) {
  if (pos < 85) return as_rgb_color_comps(255 - pos * 3, pos * 3, 0);

  if (pos < 170) {
    const uint8_t offset = pos - 85;
    return as_rgb_color_comps(0, 255 - offset * 3, offset * 3);
  }

  const uint8_t offset = pos - 170;
  return as_rgb_color_comps(offset * 3, 0, 255 - offset * 3);
}

void rgb_color_init(uint16_t rgb_pin, bool is_rgbw) {
  int sm = 0;
  uint offset = pio_add_program(pio0, &ws2812_program);
  ws2812_program_init(pio0, sm, offset, rgb_pin, 800000, is_rgbw);
}

void rgb_color_put(rgb_color c) {
    pio_sm_put_blocking(pio0, 0, c << 8u);
}
