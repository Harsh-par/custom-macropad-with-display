#include <stdlib.h>
#include "pico/stdlib.h" 

#include "tusb.h"

#include "keys.h"
#include "actions.h"
#include "constants.h"

void key_gpio_init(void){
    gpio_init(PIN_PICO_LED);
    gpio_set_dir(PIN_PICO_LED, GPIO_OUT);

    for(enum key_id key_id = KEY_A; key_id < KEY_COUNT; key_id++){
        uint8_t pin = key_pin_map[key_id];
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_up(pin);
    }
}

void scan_key_press(uint8_t key_state[KEY_COUNT], uint8_t previous_key_state[KEY_COUNT], uint64_t current_time_us, uint64_t previous_time_us[KEY_COUNT], uint8_t encoder_layer){
    for(enum key_id key_id = KEY_A; key_id < KEY_COUNT; key_id++){
        key_state[key_id] = !gpio_get(key_pin_map[key_id]);
            
        if(key_state[key_id] && !previous_key_state[key_id] && tud_hid_ready() && current_time_us - previous_time_us[key_id] > KEY_DEBOUNCE_US){
            handle_key_press(encoder_layer, key_id);
            previous_time_us[key_id] = current_time_us;
        }

        previous_key_state[key_id] = key_state[key_id];
    }
}

void handle_key_press(enum layer_id layer, enum key_id key){
    action_handler handler = key_action_map[layer][key].on_press;

    if(handler) handler();
}

static hid_map_t queue_events[QUEUE_SIZE];
static uint8_t   queue_tail = 0;
static uint8_t   queue_head = 0;

static inline bool queue_empty(void){
    return (queue_tail == queue_head);
}

static inline void queue_push(uint8_t modifier, uint8_t keycode){
    queue_events[queue_tail] = (hid_map_t){ modifier, keycode };
    queue_tail = (queue_tail + 1) % QUEUE_SIZE;
}

static inline hid_map_t queue_pop(void){
    hid_map_t event = queue_events[queue_head];
    queue_head = (queue_head + 1) % QUEUE_SIZE;

    return event;
}

void macro_key_press(uint8_t modifier, uint8_t keycode){
    queue_push(modifier, keycode);
    queue_push(HID_KEY_NONE, HID_KEY_NONE);
}

void macro_type_url(const char* url){
    hid_map_t current_key = {0, 0};
    macro_key_press(KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_R);

    while(*url){
        char character = *url;
        current_key = char_hid_map[character];
        macro_key_press(current_key.modifier, current_key.keycode);
        url++;
    }

    macro_key_press(HID_KEY_NONE, HID_KEY_ENTER);
}

void macro_type_text(const char* text){
    hid_map_t current_key = {0, 0};

    while (*text) {
        char character = *text;
        current_key = char_hid_map[character];
        macro_key_press(current_key.modifier, current_key.keycode);
        text++;
    }
}

void macro_task(uint64_t current_time_us){
    static uint64_t delay_time_us    = 0;
    static uint64_t previous_time_us = 0;

    if(!queue_empty() && current_time_us - previous_time_us >= delay_time_us){
        delay_time_us = 0;

        hid_map_t current_event = queue_pop();
        uint8_t   keycode[6]    = { current_event.keycode, 0, 0, 0, 0, 0 };
        
        sleep_ms(6); 
        tud_task();     

        tud_hid_keyboard_report(0, current_event.modifier, keycode);

        //When pressing enter or WIN + R need to delay for a bit
        if(current_event.keycode == HID_KEY_ENTER){
            delay_time_us = 150*1000;
        }
        else if(current_event.modifier == KEYBOARD_MODIFIER_LEFTGUI && current_event.keycode == HID_KEY_R){
            delay_time_us = 150*1000;
        }
        else sleep_ms(2);
        
        tud_task();
        previous_time_us = current_time_us;
    }
}