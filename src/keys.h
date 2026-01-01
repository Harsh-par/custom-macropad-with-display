#ifndef KEYS_H
#define KEYS_H

#include "tusb.h"

#include "actions.h"
#include "constants.h"

void key_gpio_init(void);

void scan_key_press(uint8_t  key_state[KEY_COUNT], 
                    uint8_t  previous_key_state[KEY_COUNT], 
                    uint64_t current_time_us, 
                    uint64_t previous_time_us[KEY_COUNT], 
                    uint8_t  encoder_layer);

void handle_key_press(enum layer_id layer, enum key_id key);

void macro_key_press(uint8_t modifier, uint8_t keycode);
void macro_type_url(const char* url);
void macro_type_text(const char* text);

void macro_task(uint64_t current_time_us);

static const uint8_t key_pin_map[KEY_COUNT] = {
    [KEY_A] = PIN_SWITCH_A,
    [KEY_B] = PIN_SWITCH_B,
    [KEY_C] = PIN_SWITCH_C,
    [KEY_D] = PIN_SWITCH_D,
    [KEY_E] = PIN_SWITCH_E,
    [KEY_F] = PIN_SWITCH_F,
};

typedef void (*action_handler)(void);

typedef struct key_action{ action_handler on_press; } key_action_t;

static const key_action_t key_action_map[LAYER_COUNT][KEY_COUNT] = {
    [LAYER_1] = {
        [KEY_A] = { action_copy       },
        [KEY_B] = { action_undo       },
        [KEY_C] = { action_screenshot },
        [KEY_D] = { action_paste      },
        [KEY_E] = { action_cut        },
        [KEY_F] = { action_select     },  
    },
    
    [LAYER_2] = {
        [KEY_A] = { action_open_google_drive },
        [KEY_B] = { action_open_youtube      },
        [KEY_C] = { action_open_github       },
        [KEY_D] = { action_open_google       },
        [KEY_E] = { action_open_discord      },
        [KEY_F] = { action_open_chatgpt      },
    },

    [LAYER_3] = {
        [KEY_A] = { action_zoom_in },
        [KEY_B] = { action_zoom_out },
        [KEY_C] = { action_save },
        [KEY_D] = { action_tab_open },
        [KEY_E] = { action_tab_close },
        [KEY_F] = { action_open }, 
    },

    [LAYER_4] = {
        [KEY_A] = { action_open_taskmanager },
        [KEY_B] = { action_window_close },
        [KEY_C] = { action_refresh },
        [KEY_D] = { action_find },
        [KEY_E] = { action_desktop_show },
        [KEY_F] = { action_lock_computer }, 
    },

    [LAYER_5] = {
        [KEY_A] = { action_volume_up       },
        [KEY_B] = { action_volume_down     },
        [KEY_C] = { action_mute            },
        [KEY_D] = { action_brightness_up   },
        [KEY_E] = { action_brightness_down },
        [KEY_F] = { action_play_pause      }, 
    }
};

typedef struct hid_map{
    uint8_t modifier; 
    uint8_t keycode; 
} hid_map_t;

static const hid_map_t char_hid_map[MAX_CHAR] = {
    [0 ... 31] = { HID_KEY_NONE, HID_KEY_NONE },

    [' '] = { HID_KEY_NONE, HID_KEY_SPACE },
    ['0'] = { HID_KEY_NONE, HID_KEY_0 },
    [')'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_0 },
    ['1'] = { HID_KEY_NONE, HID_KEY_1 },
    ['!'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_1 },
    ['2'] = { HID_KEY_NONE, HID_KEY_2 },
    ['@'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_2 },
    ['3'] = { HID_KEY_NONE, HID_KEY_3 },
    ['#'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_3 },
    ['4'] = { HID_KEY_NONE, HID_KEY_4 },
    ['$'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_4 },
    ['5'] = { HID_KEY_NONE, HID_KEY_5 },
    ['%'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_5 },
    ['6'] = { HID_KEY_NONE, HID_KEY_6 },
    ['^'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_6 },
    ['7'] = { HID_KEY_NONE, HID_KEY_7 },
    ['&'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_7 },
    ['8'] = { HID_KEY_NONE, HID_KEY_8 },
    ['*'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_8 },
    ['9'] = { HID_KEY_NONE, HID_KEY_9 },
    ['('] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_9 },

    ['a'] = { HID_KEY_NONE, HID_KEY_A },
    ['b'] = { HID_KEY_NONE, HID_KEY_B },
    ['c'] = { HID_KEY_NONE, HID_KEY_C },
    ['d'] = { HID_KEY_NONE, HID_KEY_D },
    ['e'] = { HID_KEY_NONE, HID_KEY_E },
    ['f'] = { HID_KEY_NONE, HID_KEY_F },
    ['g'] = { HID_KEY_NONE, HID_KEY_G },
    ['h'] = { HID_KEY_NONE, HID_KEY_H },
    ['i'] = { HID_KEY_NONE, HID_KEY_I },
    ['j'] = { HID_KEY_NONE, HID_KEY_J },
    ['k'] = { HID_KEY_NONE, HID_KEY_K },
    ['l'] = { HID_KEY_NONE, HID_KEY_L },
    ['m'] = { HID_KEY_NONE, HID_KEY_M },
    ['n'] = { HID_KEY_NONE, HID_KEY_N },
    ['o'] = { HID_KEY_NONE, HID_KEY_O },
    ['p'] = { HID_KEY_NONE, HID_KEY_P },
    ['q'] = { HID_KEY_NONE, HID_KEY_Q },
    ['r'] = { HID_KEY_NONE, HID_KEY_R },
    ['s'] = { HID_KEY_NONE, HID_KEY_S },
    ['t'] = { HID_KEY_NONE, HID_KEY_T },
    ['u'] = { HID_KEY_NONE, HID_KEY_U },
    ['v'] = { HID_KEY_NONE, HID_KEY_V },
    ['w'] = { HID_KEY_NONE, HID_KEY_W },
    ['x'] = { HID_KEY_NONE, HID_KEY_X },
    ['y'] = { HID_KEY_NONE, HID_KEY_Y },
    ['z'] = { HID_KEY_NONE, HID_KEY_Z },

    ['A'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_A },
    ['B'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_B },
    ['C'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_C },
    ['D'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_D },
    ['E'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_E },
    ['F'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_F },
    ['G'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_G },
    ['H'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_H },
    ['I'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_I },
    ['J'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_J },
    ['K'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_K },
    ['L'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_L },
    ['M'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_M },
    ['N'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_N },
    ['O'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_O },
    ['P'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_P },
    ['Q'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_Q },
    ['R'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_R },
    ['S'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_S },
    ['T'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_T },
    ['U'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_U },
    ['V'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_V },
    ['W'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_W },
    ['X'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_X },
    ['Y'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_Y },
    ['Z'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_Z },

    ['-'] = { HID_KEY_NONE, HID_KEY_MINUS },
    ['_'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_MINUS },
    ['='] = { HID_KEY_NONE, HID_KEY_EQUAL },
    ['+'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_EQUAL },
    ['['] = { HID_KEY_NONE, HID_KEY_BRACKET_LEFT },
    ['{'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_BRACKET_LEFT },
    [']'] = { HID_KEY_NONE, HID_KEY_BRACKET_RIGHT },
    ['}'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_BRACKET_RIGHT },
    [';'] = { HID_KEY_NONE, HID_KEY_SEMICOLON },
    [':'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_SEMICOLON },
    ['\''] = { HID_KEY_NONE, HID_KEY_APOSTROPHE },
    ['"']  = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_APOSTROPHE },
    ['`'] = { HID_KEY_NONE, HID_KEY_GRAVE },
    ['~'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_GRAVE },
    [','] = { HID_KEY_NONE, HID_KEY_COMMA },
    ['<'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_COMMA },
    ['.'] = { HID_KEY_NONE, HID_KEY_PERIOD },
    ['>'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_PERIOD },
    ['/'] = { HID_KEY_NONE, HID_KEY_SLASH },
    ['?'] = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_SLASH },
    ['\\'] = { HID_KEY_NONE, HID_KEY_BACKSLASH },
    ['|']  = { KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_BACKSLASH },

    [127] = { HID_KEY_NONE, HID_KEY_NONE },
};

#endif
