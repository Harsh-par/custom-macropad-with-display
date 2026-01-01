#ifndef GUI_H 
#define GUI_H 

#include "constants.h"
#include "st7789.h"

extern const uint16_t bitmap_nothing[];

extern const uint16_t bitmap_chatgpt[];
extern const uint16_t bitmap_youtube[];
extern const uint16_t bitmap_discord[];
extern const uint16_t bitmap_google[];
extern const uint16_t bitmap_github[];
extern const uint16_t bitmap_googledrive[];

extern const uint16_t bitmap_copy[];
extern const uint16_t bitmap_paste[];
extern const uint16_t bitmap_select[];
extern const uint16_t bitmap_cut[];
extern const uint16_t bitmap_undo[];
extern const uint16_t bitmap_screenshot[];

extern const uint16_t bitmap_zoom_out[];
extern const uint16_t bitmap_close_tab[];
extern const uint16_t bitmap_open_tab[];
extern const uint16_t bitmap_open[];
extern const uint16_t bitmap_save[];
extern const uint16_t bitmap_zoom_in[];

extern const uint16_t bitmap_find[];
extern const uint16_t bitmap_lock[];
extern const uint16_t bitmap_task_man[];
extern const uint16_t bitmap_desktop[];
extern const uint16_t bitmap_refresh[];
extern const uint16_t bitmap_close_window[];

extern const uint16_t bitmap_volume_down[];
extern const uint16_t bitmap_silent[];
extern const uint16_t bitmap_pause_play[];
extern const uint16_t bitmap_bri_up[];
extern const uint16_t bitmap_bri_down[];
extern const uint16_t bitmap_volume_up[];

extern const uint16_t bitmap_A[];
extern const uint16_t bitmap_B[];
extern const uint16_t bitmap_C[];
extern const uint16_t bitmap_D[];
extern const uint16_t bitmap_E[];
extern const uint16_t bitmap_F[];
extern const uint16_t bitmap_G[];
extern const uint16_t bitmap_H[];
extern const uint16_t bitmap_I[];
extern const uint16_t bitmap_J[];
extern const uint16_t bitmap_K[];
extern const uint16_t bitmap_L[];
extern const uint16_t bitmap_M[];
extern const uint16_t bitmap_N[];
extern const uint16_t bitmap_O[];
extern const uint16_t bitmap_P[];
extern const uint16_t bitmap_Q[];
extern const uint16_t bitmap_R[];
extern const uint16_t bitmap_S[];
extern const uint16_t bitmap_T[];
extern const uint16_t bitmap_U[];
extern const uint16_t bitmap_V[];
extern const uint16_t bitmap_W[];
extern const uint16_t bitmap_X[];
extern const uint16_t bitmap_Y[];
extern const uint16_t bitmap_Z[];
extern const uint16_t bitmap_Space[];

static const uint16_t* char_bitmap_map[MAX_CHAR] = {
    ['A'] = bitmap_A,
    ['B'] = bitmap_B,
    ['C'] = bitmap_C,
    ['D'] = bitmap_D,
    ['E'] = bitmap_E,
    ['F'] = bitmap_F,
    ['G'] = bitmap_G,
    ['H'] = bitmap_H,
    ['I'] = bitmap_I,
    ['J'] = bitmap_J,
    ['K'] = bitmap_K,
    ['L'] = bitmap_L,
    ['M'] = bitmap_M,
    ['N'] = bitmap_N,
    ['O'] = bitmap_O,
    ['P'] = bitmap_P,
    ['Q'] = bitmap_Q,
    ['R'] = bitmap_R,
    ['S'] = bitmap_S,
    ['T'] = bitmap_T,
    ['U'] = bitmap_U,
    ['V'] = bitmap_V,
    ['W'] = bitmap_W,
    ['X'] = bitmap_X,
    ['Y'] = bitmap_Y,
    ['Z'] = bitmap_Z,
    [' '] = bitmap_Space,
};

static const uint16_t* key_bitmap_map[LAYER_COUNT][KEY_COUNT] = {
    [LAYER_1] = {
        [KEY_A] = bitmap_copy,
        [KEY_B] = bitmap_undo,
        [KEY_C] = bitmap_screenshot,
        [KEY_D] = bitmap_paste,
        [KEY_E] = bitmap_cut,
        [KEY_F] = bitmap_select,  
    },
    
    [LAYER_2] = {
        [KEY_A] = bitmap_googledrive,
        [KEY_B] = bitmap_youtube,
        [KEY_C] = bitmap_github,
        [KEY_D] = bitmap_google,
        [KEY_E] = bitmap_discord,
        [KEY_F] = bitmap_chatgpt,
    },

    [LAYER_3] = {
        [KEY_A] = bitmap_zoom_in,
        [KEY_B] = bitmap_zoom_out,
        [KEY_C] = bitmap_save,
        [KEY_D] = bitmap_open_tab,
        [KEY_E] = bitmap_close_tab,
        [KEY_F] = bitmap_open,  
    },

    [LAYER_4] = {
        [KEY_A] = bitmap_task_man,
        [KEY_B] = bitmap_close_window,
        [KEY_C] = bitmap_refresh,
        [KEY_D] = bitmap_find,
        [KEY_E] = bitmap_desktop,
        [KEY_F] = bitmap_lock, 
    },

    [LAYER_5] = {
        [KEY_A] = bitmap_volume_up,
        [KEY_B] = bitmap_volume_down,
        [KEY_C] = bitmap_silent,
        [KEY_D] = bitmap_bri_up,
        [KEY_E] = bitmap_bri_down,
        [KEY_F] = bitmap_pause_play,  
    }

};

static st7789_t display = {
    .spi     = spi0,
    .spi_clk = TFT_SPI_CLK,
    .width   = TFT_WIDTH,
    .height  = TFT_HEIGHT,
    .pin_blk = PIN_TFT_BLK,
    .pin_cs  = PIN_TFT_CS,
    .pin_dc  = PIN_TFT_DC,
    .pin_rst = PIN_TFT_RST,
    .pin_scl = PIN_TFT_SCL,
    .pin_sda = PIN_TFT_SDA
};

void gui_init(void);
void gui_draw_lower(uint8_t current_layer);
void gui_draw_middle(uint8_t current_layer);
void gui_draw_upper(uint8_t current_layer);

#endif 
