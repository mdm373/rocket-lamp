#ifndef ADC_READ_INCLUDE
#define ADC_READ_INCLUDE

#include "pico/stdlib.h"
#include "hardware/adc.h"

#define ADC_MAX (1<<12);

void read_adc_init(uint16_t adc_pin);
float read_adc_percent();

#endif