#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "tusb.h"

#include "constants.h"
#include "keys.h"
#include "encoder.h"
#include "backlight.h"
#include "gui.h"

//main.c of this project

void core1_main();

volatile uint8_t  current_key_state[KEY_COUNT]  = {0, 0, 0, 0, 0, 0};
volatile uint8_t  previous_key_state[KEY_COUNT] = {0, 0, 0, 0, 0, 0};
volatile uint64_t previous_time_us[KEY_COUNT]   = {0, 0, 0, 0, 0, 0};

volatile uint8_t  encoder_state = 0;
volatile uint8_t  encoder_layer = 0;

volatile enum brightness_level current_brightness = BRIGHTNESS_1;

/*
CORE0 constantly updates switch states and encoder layers, which allow key bind signals to be sent
based on the layer and key pair when pressed.
*/
int main(){
    key_gpio_init();
    encoder_gpio_init();
    backlight_gpio_init(current_brightness);
    gui_init();
    tusb_init();

    multicore_launch_core1(core1_main);

    while(!tud_mounted()) tud_task();
    
    while(true){
        uint64_t current_time_us = time_us_64();
        
        encoder_state = get_encoder_state();
        encoder_layer = get_encoder_layer();
        
        scan_key_press((uint8_t*)current_key_state, (uint8_t*)previous_key_state, current_time_us, (uint64_t*)previous_time_us, encoder_layer);
        
        macro_task(current_time_us);
        tud_task(); 
    }
}


/*
CORE1 only reads global values modified by CORE0 such as the encoder layer & switch states.
All computations related to the tft display are done on CORE1 based on those global values but CORE1 never modifies those values.
*/
void core1_main(){   
    uint64_t previous_time_us       = time_us_64();
    uint8_t  previous_encoder_layer = LAYER_COUNT;
    
    while(true){
      uint64_t current_time_us       = time_us_64();
      uint8_t  current_encoder_layer = encoder_layer;
      uint8_t  current_encoder_state = encoder_state;

      if(previous_encoder_layer != current_encoder_layer && current_time_us - previous_time_us >= ENCODER_DEBOUNCE_US){       
        gui_draw_lower(current_encoder_layer);
        gui_draw_middle(current_encoder_layer);
        gui_draw_upper(current_encoder_layer);

        previous_time_us       = current_time_us;
        previous_encoder_layer = current_encoder_layer;
      }

      if(current_encoder_state && current_time_us - previous_time_us >= 10*ENCODER_DEBOUNCE_US){ 
        current_brightness = (current_brightness + 1) % BRIGHTNESS_LEVELS;

        backlight_set_level(current_brightness);

        previous_time_us = current_time_us;
      }    
    }
}
