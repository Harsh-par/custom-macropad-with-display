#ifndef CONSTANTS_H
#define CONSTANTS_H

//Enums used for Key and Layers
enum key_id{
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_COUNT
};

enum layer_id{
    LAYER_1,
    LAYER_2,
    LAYER_3,
    LAYER_4,
    LAYER_5,
    LAYER_COUNT
};

#define GPIO_ON  1
#define GPIO_OFF 0

#define KEY_DEBOUNCE_US   175000
#define KEY_DELAY_TIME_MS 220

//GPIO Pin Definitions
#define PIN_PICO_LED PICO_DEFAULT_LED_PIN

#define PIN_SWITCH_A 5
#define PIN_SWITCH_B 6
#define PIN_SWITCH_C 7
#define PIN_SWITCH_D 8
#define PIN_SWITCH_E 9
#define PIN_SWITCH_F 10
#define PIN_SWITCH_G 11

#define PIN_ENCODER_BUTTON  12
#define PIN_ENCODER_PHASE_A 14
#define PIN_ENCODER_PHASE_B 15

//Encoder Definitions
#define ENCODER_STEP_SIZE   1
#define ENCODER_DEBOUNCE_US 25000

//TFT Pin and Display Definitions
#define PIN_TFT_BLK 21
#define PIN_TFT_RST 20
#define PIN_TFT_CS  17
#define PIN_TFT_DC  16
#define PIN_TFT_SDA 19
#define PIN_TFT_SCL 18

#define TFT_HEIGHT 280
#define TFT_WIDTH  240

#define TFT_SPI_CLK 40000000

//Event Queue Definitions
#define QUEUE_SIZE 1024

//Bitmap Font Definitions
#define FONT_HEIGHT 30
#define FONT_WIDTH  20

//ST7789 Definitions
#define ST7789_OFFSET_X  0
#define ST7789_OFFSET_Y  20

//ST7789 Colors
#define ST7789_COLOR_BLACK       0x0000 
#define ST7789_COLOR_WHITE       0xFFFF 
#define ST7789_COLOR_RED         0xF800
#define ST7789_COLOR_GREEN       0x07E0
#define ST7789_COLOR_BLUE        0x001F
#define ST7789_COLOR_YELLOW      0xFFE0
#define ST7789_COLOR_CYAN        0x07FF
#define ST7789_COLOR_MAGENTA     0xF81F
#define ST7789_COLOR_ORANGE      0xFC00
#define ST7789_COLOR_PINK        0xF81F
#define ST7789_COLOR_GRAY        0x8410
#define ST7789_COLOR_LIGHT_BLUE  0x7D7C
#define ST7789_COLOR_SKY_BLUE    0x867D
#define ST7789_COLOR_DEEP_BLUE   0x0010
#define ST7789_COLOR_NAVY        0x001F
#define ST7789_COLOR_LIGHT_GREEN 0x87F0
#define ST7789_COLOR_LIME        0x07E0
#define ST7789_COLOR_DARK_GREEN  0x03E0
#define ST7789_COLOR_LIGHT_RED   0xF810
#define ST7789_COLOR_CRIMSON     0xC810
#define ST7789_COLOR_DARK_RED    0x8000
#define ST7789_COLOR_LIGHT_GRAY  0xC618
#define ST7789_COLOR_DARK_GRAY   0x4208
#define ST7789_COLOR_SILVER      0xBDF7  
#define ST7789_COLOR_BROWN       0xA145 
#define ST7789_COLOR_VIOLET      0x915C  
#define ST7789_COLOR_BEIGE       0xF7BB  
#define ST7789_COLOR_TURQUOISE   0x471F  
#define ST7789_COLOR_OLIVE       0x7BE0  

//ST7789 Register Addresses
#define ST7789_CMD_SWRESET  0x01
#define ST7789_CMD_SLPOUT   0x11
#define ST7789_CMD_COLMOD   0x3A
#define ST7789_CMD_MADCTL   0x36
#define ST7789_CMD_CASET    0x2A
#define ST7789_CMD_RASET    0x2B
#define ST7789_CMD_RAMWR    0x2C
#define ST7789_CMD_DISPON   0x29
#define ST7789_CMD_INVON    0x21
#define ST7789_CMD_NORON    0x13
#define ST7789_CMD_VSCRDEF  0x33
#define ST7789_CMD_VSCRSADD 0x37
#define ST7789_CMD_PORCTRL  0xB2
#define ST7789_CMD_GCTRL    0xB7
#define ST7789_CMD_VCOMS    0xBB
#define ST7789_CMD_LCMCTRL  0xC0
#define ST7789_CMD_IDSET    0xC2
#define ST7789_CMD_VDVVRHEN 0xC3
#define ST7789_CMD_VRHS     0xC4
#define ST7789_CMD_VCMOFSET 0xC5
#define ST7789_CMD_FRCTRL2  0xC6
#define ST7789_CMD_PWCTRL1  0xD0
#define ST7789_CMD_PVGAMCTRL 0xE0
#define ST7789_CMD_NVGAMCTRL 0xE1

//GC9A01 Colors
#define GC9A01_COLOR_BLACK      0xFFFF  
#define GC9A01_COLOR_WHITE      0x0000  
#define GC9A01_COLOR_RED        0xFFE0  
#define GC9A01_COLOR_BLUE       0x07FF 
#define GC9A01_COLOR_MAGENTA    0x07E0  
#define GC9A01_COLOR_LIGHTBLUE  0x001F   

//GC9A01 Register Addresses
#define GC9A01_CMD_NOP        0x00
#define GC9A01_CMD_SWRESET    0x01
#define GC9A01_CMD_CASET      0x2A
#define GC9A01_CMD_RASET      0x2B
#define GC9A01_CMD_RAMWR      0x2C
#define GC9A01_CMD_DISPON     0x29
#define GC9A01_CMD_SLPOUT     0x11
#define GC9A01_CMD_MADCTL     0x36
#define GC9A01_CMD_COLMOD     0x3A
#define GC9A01_CMD_TEON       0x35
#define GC9A01_CMD_EF         0xEF
#define GC9A01_CMD_EB         0xEB
#define GC9A01_CMD_FE         0xFE
#define GC9A01_CMD_84         0x84
#define GC9A01_CMD_85         0x85
#define GC9A01_CMD_86         0x86
#define GC9A01_CMD_87         0x87
#define GC9A01_CMD_88         0x88
#define GC9A01_CMD_89         0x89
#define GC9A01_CMD_8A         0x8A
#define GC9A01_CMD_8B         0x8B
#define GC9A01_CMD_8C         0x8C
#define GC9A01_CMD_8D         0x8D
#define GC9A01_CMD_8E         0x8E
#define GC9A01_CMD_8F         0x8F
#define GC9A01_CMD_B6         0xB6
#define GC9A01_CMD_90         0x90
#define GC9A01_CMD_BD         0xBD
#define GC9A01_CMD_BC         0xBC
#define GC9A01_CMD_FF         0xFF
#define GC9A01_CMD_C3         0xC3
#define GC9A01_CMD_C4         0xC4
#define GC9A01_CMD_C9         0xC9
#define GC9A01_CMD_BE         0xBE
#define GC9A01_CMD_E1         0xE1
#define GC9A01_CMD_DF         0xDF
#define GC9A01_CMD_F0         0xF0
#define GC9A01_CMD_F1         0xF1
#define GC9A01_CMD_F2         0xF2
#define GC9A01_CMD_F3         0xF3
#define GC9A01_CMD_ED         0xED
#define GC9A01_CMD_AE         0xAE
#define GC9A01_CMD_CD         0xCD
#define GC9A01_CMD_BSTL       0x70
#define GC9A01_CMD_E8         0xE8
#define GC9A01_CMD_62         0x62
#define GC9A01_CMD_63         0x63
#define GC9A01_CMD_64         0x64
#define GC9A01_CMD_66         0x66
#define GC9A01_CMD_67         0x67
#define GC9A01_CMD_74         0x74
#define GC9A01_CMD_98         0x98

#define MAX_CHAR 128

#endif