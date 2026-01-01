#ifndef BACKLIGHT_H
#define BACKLIGHT_H

#include "constants.h"

enum brightness_level{
  BRIGHTNESS_1,
  BRIGHTNESS_2,
  BRIGHTNESS_3,
  BRIGHTNESS_4,
  BRIGHTNESS_5,
  BRIGHTNESS_LEVELS
};

void backlight_gpio_init(enum brightness_level brightness);
void backlight_set_level(enum brightness_level brightness);

#endif