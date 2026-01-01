#ifndef ENCODER_H
#define ENCODER_H

#include "pico/stdlib.h"

void encoder_gpio_init(void);
uint16_t get_encoder_layer();
uint8_t  get_encoder_state();

#endif
