#ifndef RGB_COLOR_INCLUDE
#define RGB_COLOR_INCLUDE

#include "pico/stdlib.h"
#include "stdbool.h"
#include "ws2812.pio.h"
#include "hardware/pio.h"

typedef uint32_t rgb_color;
typedef struct RgbColorComps_T {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RgbColorComps;

rgb_color comps_as_rgb_color(RgbColorComps comps);
rgb_color arr_as_rgb_color(uint8_t arr[3]);
rgb_color comps_as_rgb_color_scaled(RgbColorComps comps, float scale);
rgb_color as_rgb_color(uint8_t r, uint8_t g, uint8_t b);
RgbColorComps as_rgb_color_comps(uint8_t r, uint8_t g, uint8_t b);
RgbColorComps wheel_color(uint8_t position);

void rgb_color_init(uint16_t rgb_pin, bool is_rgbw);
void rgb_color_put(rgb_color c);

#endif