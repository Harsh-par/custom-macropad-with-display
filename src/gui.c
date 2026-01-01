#include "hardware/spi.h"

#include "constants.h"
#include "st7789.h"
#include "gui.h"

#define BOX_START_Y  264
#define BOX_START_X  45
#define BOX_WIDTH    22
#define BOX_HEIGHT   15
#define BOX_MARGIN_X 10

#define KEYBOX_START_Y  25
#define KEYBOX_START_X  40
#define KEYBOX_WIDTH    70
#define KEYBOX_HEIGHT   70
#define KEYBOX_MARGIN_Y 5
#define KEYBOX_MARGIN_X 5
#define KEYBOX_ROWS     3
#define KEYBOX_COLUMNS  2

#define ENC_START_Y 2
#define ENC_START_X 40
#define ENC_WIDTH   160
#define ENC_HEIGHT  20

void gui_write_text(uint8_t x, uint8_t y, char *string);
/*
Function to initialize the background of the GUI.
*/
void gui_init(void){
    st7789_init(&display);  
}

/*
Function to draw upper  part of the GUI, depends on the encoder state and only changes when button is pressed.
*/
void gui_draw_upper(uint8_t current_layer){
    uint16_t x = ENC_START_X;
    uint16_t y = ENC_START_Y;
    uint16_t w = ENC_WIDTH;
    uint16_t h = ENC_HEIGHT;

    switch(current_layer){
        case LAYER_1: 
            gui_write_text(0, y, "           "); 
            gui_write_text(x+20, y, "MACROS"); 
            break;
        case LAYER_2: 
            gui_write_text(0, y, "           "); 
            gui_write_text(x+40, y, "APPS"); 
            break;
        case LAYER_3: 
            gui_write_text(0, y, "           "); 
            gui_write_text(x+20, y, "BROWSE"); 
            break;
        case LAYER_4: 
            gui_write_text(0, y, "           "); 
            gui_write_text(x+20, y, "MANAGE"); 
            break;
        case LAYER_5: 
            gui_write_text(0, y, "           "); 
            gui_write_text(x+10, y, "UTILITY"); 
            break;
        default: break;
    }

    //if(current_encoder_state) st7789_draw_rectangle(&display, x+3, y+3, w-6, h-6, ST7789_COLOR_SILVER);
}

/*
Function to draw middle part of the GUI, depends on the encoder layer and only changes when layer changes.
*/
void gui_draw_middle(uint8_t current_layer){

    for (enum key_id key_id = KEY_A; key_id < KEY_COUNT; key_id++){
        const uint16_t* bitmap = key_bitmap_map[current_layer][key_id];
        
        if(bitmap){
            uint8_t row    = key_id % KEYBOX_ROWS;
            uint8_t column;

            if(key_id < 3) column = 0;
            else column = 1;

            uint16_t y = KEYBOX_START_Y + KEYBOX_MARGIN_Y + row * (2 * KEYBOX_MARGIN_Y + KEYBOX_HEIGHT);
            uint16_t x = KEYBOX_START_X + KEYBOX_MARGIN_X + column * (2 * KEYBOX_MARGIN_X + KEYBOX_WIDTH);

            uint16_t w = KEYBOX_WIDTH;
            uint16_t h = KEYBOX_HEIGHT;
            
            st7789_draw_bitmap(&display, x, y, w, h, bitmap);
        }
    }    
}

/*
Function to draw lower part of the GUI, depends on the encoder layer and only changes when layer changes.
*/
void gui_draw_lower(uint8_t current_layer){

    uint16_t y = BOX_START_Y;
    
    for(enum layer_id layer = LAYER_1; layer < LAYER_COUNT; layer++){
        uint16_t x = BOX_START_X + layer*(BOX_MARGIN_X + BOX_WIDTH);
        uint16_t w = BOX_WIDTH;
        uint16_t h = BOX_HEIGHT; 

        st7789_draw_rectangle_filled(&display, x, y, w, h, ST7789_COLOR_DARK_GRAY);
        st7789_draw_rectangle(&display, x, y, w, h, ST7789_COLOR_BLACK);
        
        if(layer == current_layer){
            st7789_draw_rectangle_filled(&display, x+2, y+2, w-4,h-4, ST7789_COLOR_SILVER);
        }
        else st7789_draw_rectangle(&display, x+1, y+1, w-2, h-2, ST7789_COLOR_GRAY); 
    }
}

void gui_write_text(uint8_t x, uint8_t y, char *string){
    for(int i = 0; string[i]; i++){
        st7789_draw_bitmap(&display, x + i*FONT_WIDTH, y, FONT_WIDTH, FONT_HEIGHT, char_bitmap_map[(uint8_t)string[i]]);
    }
}
