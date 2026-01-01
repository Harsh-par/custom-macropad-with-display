#include "pico/stdlib.h"

#include "hardware/irq.h"
#include "hardware/pwm.h"

#include "constants.h"
#include "encoder.h"

static volatile uint16_t encoder_layer = 0;

static volatile uint64_t previous_increment_us = 0; 
static volatile uint64_t previous_decrement_us = 0; 

/*
Encoder rotation handler function based on https://github.com/mo-thunderz/RotaryEncoder modified to be able to use it with raspberry pi pico's libraries
*/
static void encoder_handler(uint gpio, uint32_t events){
  static const int8_t encoder_state_table[]  = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

  uint64_t current_time_us = time_us_64();
  
  static uint8_t previous_states = 0b00000011;  
  static int8_t encoder_value = 0;  

  previous_states = previous_states << 2; 

  if(gpio_get(PIN_ENCODER_PHASE_A)) previous_states |= 0b00000010; 
  if(gpio_get(PIN_ENCODER_PHASE_B)) previous_states |= 0b00000001; 
  
  encoder_value = encoder_value + encoder_state_table[( previous_states & 0b00001111 )];

  if(encoder_value > 3){      
    int8_t encoder_step = 1;

    if(current_time_us - previous_increment_us < ENCODER_DEBOUNCE_US){
      encoder_step = ENCODER_STEP_SIZE * encoder_step; 
    }

    previous_increment_us = current_time_us;
    encoder_layer = (encoder_layer + encoder_step + LAYER_COUNT ) % LAYER_COUNT;            
    encoder_value = 0;
  }
  else if(encoder_value < -3){        
    int8_t encoder_step = -1;

    if(current_time_us - previous_decrement_us < ENCODER_DEBOUNCE_US){
      encoder_step = ENCODER_STEP_SIZE * encoder_step; 
    }

    previous_decrement_us = current_time_us;
    encoder_layer = (encoder_layer + encoder_step + LAYER_COUNT) % LAYER_COUNT;            
    encoder_value = 0;
  }
}

/*
Initializing the gpio, configuring the pull up's and direction, and attaching callback to interupts.
*/
void encoder_gpio_init(void){
    gpio_init(PIN_ENCODER_BUTTON);
    gpio_set_dir(PIN_ENCODER_BUTTON, GPIO_IN);
    gpio_pull_up(PIN_ENCODER_BUTTON);

    gpio_init(PIN_ENCODER_PHASE_A);
    gpio_set_dir(PIN_ENCODER_PHASE_A, GPIO_IN);
    gpio_pull_up(PIN_ENCODER_PHASE_A);

    gpio_set_irq_enabled_with_callback(
        PIN_ENCODER_PHASE_A,
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
        true,
        encoder_handler
    );

    gpio_init(PIN_ENCODER_PHASE_B);
    gpio_set_dir(PIN_ENCODER_PHASE_B, GPIO_IN);
    gpio_pull_up(PIN_ENCODER_PHASE_B);

    gpio_set_irq_enabled_with_callback(
        PIN_ENCODER_PHASE_B,
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
        true,
        encoder_handler
    );
}

/*
Get current encoder layer, encoder layer changes based on interupt handler
*/
uint16_t get_encoder_layer(){
    return encoder_layer;
}

/*
Get current encoder button state, reading gpio at pin.
*/
uint8_t  get_encoder_state(){
    return !gpio_get(PIN_ENCODER_BUTTON);
}
