#include "constants.h"
#include "gc9a01.h"

static inline void set_cs_low(gc9a01_t *display) { gpio_put(display->pin_cs, GPIO_OFF); }
static inline void set_cs_high(gc9a01_t *display){ gpio_put(display->pin_cs, GPIO_ON);  }

static inline void set_dc_command(gc9a01_t *display){ gpio_put(display->pin_dc, GPIO_OFF); }
static inline void set_dc_data(gc9a01_t *display)   { gpio_put(display->pin_dc, GPIO_ON);  }

static void write_command(gc9a01_t *display, uint8_t command){
    set_dc_command(display);
    set_cs_low(display);
    spi_write_blocking(display->spi, &command, sizeof(command));
    set_cs_high(display);
}

static void write_data(gc9a01_t *display, const uint8_t *data, size_t length){
    set_dc_data(display);
    set_cs_low(display);
    spi_write_blocking(display->spi, data, length);
    set_cs_high(display);
}

static inline void write_data_byte(gc9a01_t *display, uint8_t data){
    write_data(display, &data, sizeof(data));
}

void gc9a01_set_window(gc9a01_t *display, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
    uint8_t buffer[4];

    write_command(display, GC9A01_CMD_CASET);
    buffer[0] = x0 >> 8; 
    buffer[1] = x0;
    buffer[2] = x1 >> 8; 
    buffer[3] = x1;
    write_data(display, buffer, sizeof(buffer));

    write_command(display, GC9A01_CMD_RASET);
    buffer[0] = y0 >> 8; 
    buffer[1] = y0;
    buffer[2] = y1 >> 8; 
    buffer[3] = y1;
    write_data(display, buffer, sizeof(buffer));

    write_command(display, GC9A01_CMD_RAMWR);
}

void gc9a01_draw_pixel(gc9a01_t *display, uint16_t x, uint16_t y, uint16_t color){
    gc9a01_set_window(display, x, y, x, y);
    uint8_t buffer[2] = {color >> 8, color};
    write_data(display, buffer, sizeof(buffer));
}

void gc9a01_draw_vline(gc9a01_t *display, uint16_t x, uint16_t y, uint16_t height, uint16_t color){
    gc9a01_set_window(display, x, y, x, y + height-1);
    uint8_t buffer[2] = {color >> 8, color};

    for(int i=0; i<height; i++) write_data(display, buffer, sizeof(buffer));
}

void gc9a01_draw_hline(gc9a01_t *display, uint16_t x, uint16_t y, uint16_t width, uint16_t color){
    gc9a01_set_window(display, x, y, x + width-1, y);
    uint8_t buffer[2] = {color >> 8, color};
    
    for(int i=0; i<width; i++) write_data(display, buffer, sizeof(buffer));
}

void gc9a01_draw_rectangle(gc9a01_t *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color){
    gc9a01_draw_hline(display, x, y, width, color);
    gc9a01_draw_hline(display, x, y + height-1, width, color);
    gc9a01_draw_vline(display, x, y, height, color);
    gc9a01_draw_vline(display, x + width-1, y, height, color);
}

void gc9a01_draw_rectangle_filled(gc9a01_t *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color){
    gc9a01_set_window(display, x, y, x + width - 1, y + height - 1);
    
    uint8_t buffer[2] = {color >> 8, color};

    set_dc_data(display);
    set_cs_low(display);

    for(uint32_t i=0; i<(width*height); i++) spi_write_blocking(display->spi, buffer, sizeof(buffer));

    set_cs_high(display);
}


void gc9a01_draw_circle(gc9a01_t *display, uint16_t x_circle, uint16_t y_circle, uint16_t radius, uint16_t color){
    int16_t x = 0;
    int16_t y = radius;
    int16_t d = 3 - 2 * radius;

    while(y >= x){
        gc9a01_draw_pixel(display, x_circle + x, y_circle + y, color);
        gc9a01_draw_pixel(display, x_circle - x, y_circle + y, color);
        gc9a01_draw_pixel(display, x_circle + x, y_circle - y, color);
        gc9a01_draw_pixel(display, x_circle - x, y_circle - y, color);
        gc9a01_draw_pixel(display, x_circle + y, y_circle + x, color);
        gc9a01_draw_pixel(display, x_circle - y, y_circle + x, color);
        gc9a01_draw_pixel(display, x_circle + y, y_circle - x, color);
        gc9a01_draw_pixel(display, x_circle - y, y_circle - x, color);
        x++;
        if(d > 0){
            y--;
            d = d + 4 * (x - y) + 10;
        } 
        else d = d + 4 * x + 6;
    }
}

void gc9a01_fill_screen(gc9a01_t *display, uint16_t color){
    gc9a01_set_window(display, 0, 0, display->width - 1, display->height - 1);
    uint8_t buffer[2] = {color >> 8, color};

    set_dc_data(display);
    set_cs_low(display);

    for(int i=0; i<(display->width * display->height); i++) spi_write_blocking(display->spi, buffer, sizeof(buffer));

    set_cs_high(display);
}

void gc9a01_init(gc9a01_t *display){
    spi_init(display->spi, display->spi_clk);

    gpio_set_function(display->pin_scl, GPIO_FUNC_SPI);
    gpio_set_function(display->pin_sda, GPIO_FUNC_SPI);

    gpio_init(display->pin_cs); 
    gpio_set_dir(display->pin_cs, GPIO_OUT);

    gpio_init(display->pin_dc);  
    gpio_set_dir(display->pin_dc, GPIO_OUT);

    gpio_init(display->pin_rst);
    gpio_set_dir(display->pin_rst, GPIO_OUT);

    gpio_put(display->pin_rst, GPIO_OFF); 
    sleep_ms(20);
    gpio_put(display->pin_rst, GPIO_ON);
    sleep_ms(120);

    write_command(display, GC9A01_CMD_EF);
    write_command(display, GC9A01_CMD_EB); write_data_byte(display, 0x14);

    write_command(display, GC9A01_CMD_FE);
    write_command(display, GC9A01_CMD_EF);
    write_command(display, GC9A01_CMD_EB); write_data_byte(display, 0x14);

    write_command(display, GC9A01_CMD_84); write_data_byte(display, 0x40);
    write_command(display, GC9A01_CMD_85); write_data_byte(display, 0xFF);
    write_command(display, GC9A01_CMD_86); write_data_byte(display, 0xFF);
    write_command(display, GC9A01_CMD_87); write_data_byte(display, 0xFF);
    write_command(display, GC9A01_CMD_88); write_data_byte(display, 0x0A);
    write_command(display, GC9A01_CMD_89); write_data_byte(display, 0x21);
    write_command(display, GC9A01_CMD_8A); write_data_byte(display, 0x00);
    write_command(display, GC9A01_CMD_8B); write_data_byte(display, 0x80);
    write_command(display, GC9A01_CMD_8C); write_data_byte(display, 0x01);
    write_command(display, GC9A01_CMD_8D); write_data_byte(display, 0x01);
    write_command(display, GC9A01_CMD_8E); write_data_byte(display, 0xFF);
    write_command(display, GC9A01_CMD_8F); write_data_byte(display, 0xFF);

    write_command(display, GC9A01_CMD_B6); 
    write_data_byte(display, 0x00);
    write_data_byte(display, 0x00);

    write_command(display, GC9A01_CMD_MADCTL);
    write_data_byte(display, 0x40);   

    write_command(display, GC9A01_CMD_COLMOD);
    write_data_byte(display, 0x05);   

    write_command(display, GC9A01_CMD_90);
    write_data_byte(display, 0x08);
    write_data_byte(display, 0x08);
    write_data_byte(display, 0x08);
    write_data_byte(display, 0x08);

    write_command(display, GC9A01_CMD_BD); write_data_byte(display, 0x06);
    write_command(display, GC9A01_CMD_BC); write_data_byte(display, 0x00);

    write_command(display, GC9A01_CMD_FF);
    write_data_byte(display, 0x60);
    write_data_byte(display, 0x01);
    write_data_byte(display, 0x04);

    write_command(display, GC9A01_CMD_C3); write_data_byte(display, 0x13);
    write_command(display, GC9A01_CMD_C4); write_data_byte(display, 0x13);
    write_command(display, GC9A01_CMD_C9); write_data_byte(display, 0x22);

    write_command(display, GC9A01_CMD_BE); write_data_byte(display, 0x11);

    write_command(display, GC9A01_CMD_E1);
    write_data_byte(display, 0x10);
    write_data_byte(display, 0x0E);

    write_command(display, GC9A01_CMD_DF);
    write_data_byte(display, 0x21);
    write_data_byte(display, 0x0C);
    write_data_byte(display, 0x02);

    write_command(display, GC9A01_CMD_F0);
    write_data_byte(display, 0x45);
    write_data_byte(display, 0x09);
    write_data_byte(display, 0x08);
    write_data_byte(display, 0x08);
    write_data_byte(display, 0x26);
    write_data_byte(display, 0x2A);

    write_command(display, GC9A01_CMD_F1);
    write_data_byte(display, 0x43);
    write_data_byte(display, 0x70);
    write_data_byte(display, 0x72);
    write_data_byte(display, 0x36);
    write_data_byte(display, 0x37);
    write_data_byte(display, 0x6F);

    write_command(display, GC9A01_CMD_F2);
    write_data_byte(display, 0x45);
    write_data_byte(display, 0x09);
    write_data_byte(display, 0x08);
    write_data_byte(display, 0x08);
    write_data_byte(display, 0x26);
    write_data_byte(display, 0x2A);

    write_command(display, GC9A01_CMD_F3);
    write_data_byte(display, 0x43);
    write_data_byte(display, 0x70);
    write_data_byte(display, 0x72);
    write_data_byte(display, 0x36);
    write_data_byte(display, 0x37);
    write_data_byte(display, 0x6F);

    write_command(display, GC9A01_CMD_ED);
    write_data_byte(display, 0x1B);
    write_data_byte(display, 0x0B);

    write_command(display, GC9A01_CMD_AE); write_data_byte(display, 0x77);
    write_command(display, GC9A01_CMD_CD); write_data_byte(display, 0x63);

    write_command(display, GC9A01_CMD_BSTL); write_data_byte(display, 0x07);

    write_command(display, GC9A01_CMD_E8); write_data_byte(display, 0x34);

    uint8_t seq62[] = {0x18,0x0D,0x71,0xED,0x70,0x70,0x18,0x0F,0x71,0xEF,0x70,0x70};
    write_command(display, GC9A01_CMD_62); write_data(display, seq62, sizeof(seq62));

    uint8_t seq63[] = {0x18,0x11,0x71,0xF1,0x70,0x70,0x18,0x13,0x71,0xF3,0x70,0x70};
    write_command(display, GC9A01_CMD_63); write_data(display, seq63, sizeof(seq63));

    uint8_t seq64[] = {0x28,0x29,0xF1,0x01,0xF1,0x00,0x07};
    write_command(display, GC9A01_CMD_64); write_data(display, seq64, sizeof(seq64));

    uint8_t seq66[] = {0x3C,0x00,0xCD,0x67,0x45,0x45,0x10,0x00,0x00};
    write_command(display, GC9A01_CMD_66); write_data(display, seq66, sizeof(seq66));

    uint8_t seq67[] = {0x00,0x3C,0x00,0x00,0x00,0x01,0x54,0x10,0x32,0x98};
    write_command(display, GC9A01_CMD_67); write_data(display, seq67, sizeof(seq67));

    uint8_t seq74[] = {0x10,0x85,0x80,0x00,0x00,0x4E,0x00};
    write_command(display, GC9A01_CMD_74); write_data(display, seq74, sizeof(seq74));

    write_command(display, GC9A01_CMD_98); write_data_byte(display, 0x3E);

    write_command(display, GC9A01_CMD_TEON);

    write_command(display, GC9A01_CMD_SLPOUT);   
    sleep_ms(120);

    write_command(display, GC9A01_CMD_DISPON);  
    sleep_ms(50);

    gc9a01_fill_screen(display, GC9A01_COLOR_BLACK);
}


