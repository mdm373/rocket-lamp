#include "read_adc.h"

void read_adc_init(uint16_t adc_pin) {
  adc_init();
  adc_gpio_init(adc_pin);
  adc_select_input(0);
}

float read_adc_percent() {
  return adc_read() / (float)ADC_MAX;
}
