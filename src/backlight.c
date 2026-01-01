#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "backlight.h"
#include "constants.h"

/*
Frequency(SYS) = 125 MHZ
Frequency(PWM) = Frequency(SYS) / (PERIOD_COUNT)
For a 2KHz PWM Frequency we need a period count = 62500
*/ 
#define PERIOD_COUNT 62500
#define PWM_STEP     (float)(1.0 / (BRIGHTNESS_LEVELS))


void backlight_set_level(enum brightness_level brightness){
    uint slice   = pwm_gpio_to_slice_num(PIN_TFT_BLK);
    uint channel = pwm_gpio_to_channel(PIN_TFT_BLK); 

    uint16_t level = (uint16_t)(PWM_STEP * (1 + brightness) * (PERIOD_COUNT - 1));

    pwm_set_chan_level(slice, channel, level);
}

void backlight_gpio_init(enum brightness_level brightness){
    gpio_set_function(PIN_TFT_BLK, GPIO_FUNC_PWM);

    uint slice = pwm_gpio_to_slice_num(PIN_TFT_BLK);

    pwm_set_enabled(slice, true);
    pwm_set_wrap(slice, PERIOD_COUNT - 1);   
    
    backlight_set_level(brightness);
}
