#include "constants.h"
#include "st7789.h"

static inline void set_cs_low (st7789_t *display){ gpio_put(display->pin_cs, GPIO_OFF); }
static inline void set_cs_high(st7789_t *display){ gpio_put(display->pin_cs, GPIO_ON);  }

static inline void set_dc_command(st7789_t *display){ gpio_put(display->pin_dc, GPIO_OFF); }
static inline void set_dc_data   (st7789_t *display){ gpio_put(display->pin_dc, GPIO_ON);  }

static inline void set_blk_low(st7789_t *display) { gpio_put(display->pin_blk, GPIO_OFF); }
static inline void set_blk_high(st7789_t *display){ gpio_put(display->pin_blk, GPIO_ON);  }

static inline void write_command(st7789_t *display, uint8_t command){
    set_dc_command(display);
    set_cs_low(display);
    spi_write_blocking(display->spi, &command, sizeof(command));
    set_cs_high(display);
}

static inline void write_data(st7789_t *display, const uint8_t *data, size_t length){
    set_dc_data(display);
    set_cs_low(display);
    spi_write_blocking(display->spi, data, length);
    set_cs_high(display);
}

static inline void write_data_byte(st7789_t *display, uint8_t data){
    write_data(display, &data, sizeof(data));
}

void st7789_init(st7789_t *display){
    spi_init(display->spi, display->spi_clk);

    gpio_set_function(display->pin_scl, GPIO_FUNC_SPI);
    gpio_set_function(display->pin_sda, GPIO_FUNC_SPI);

    gpio_init(display->pin_cs);  gpio_set_dir(display->pin_cs, GPIO_OUT);
    gpio_init(display->pin_dc);  gpio_set_dir(display->pin_dc, GPIO_OUT);
    gpio_init(display->pin_rst); gpio_set_dir(display->pin_rst, GPIO_OUT);

    //handled in blacklight.c
    //gpio_init(display->pin_blk); gpio_set_dir(display->pin_blk, GPIO_OUT);        

    gpio_put(display->pin_rst, GPIO_OFF);
    sleep_ms(20);
    gpio_put(display->pin_rst, GPIO_ON);
    sleep_ms(120);

    write_command(display, ST7789_CMD_SWRESET);
    sleep_ms(150);

    write_command(display, ST7789_CMD_SLPOUT);
    sleep_ms(120);

    write_command(display, ST7789_CMD_PORCTRL);
    write_data(display, (uint8_t[]){0x0C,0x0C,0x00,0x33,0x33},5);

    write_command(display, ST7789_CMD_GCTRL);
    write_data_byte(display, 0x35); 

    write_command(display, ST7789_CMD_VCOMS);
    write_data_byte(display, 0x19);

    write_command(display, ST7789_CMD_LCMCTRL);
    write_data_byte(display, 0x2C);

    write_command(display, ST7789_CMD_IDSET);
    write_data(display, (uint8_t[]){0x01,0xFF},2);

    write_command(display, ST7789_CMD_VDVVRHEN);
    write_data_byte(display, 0x01);

    write_command(display, ST7789_CMD_VRHS);
    write_data_byte(display, 0x12);

    write_command(display, ST7789_CMD_VCMOFSET);
    write_data_byte(display, 0x20);

    write_command(display, ST7789_CMD_FRCTRL2);
    write_data_byte(display, 0x0F);

    write_command(display, ST7789_CMD_PWCTRL1);
    write_data(display, (uint8_t[]){0xA4,0xA1},2);

    write_command(display, ST7789_CMD_PVGAMCTRL);
    write_data(display, (uint8_t[]){0xD0,0x00,0x02,0x07,0x0A,0x28,0x32,0x44,0x42,0x06,0x0E,0x12,0x14,0x17},14);

    write_command(display, ST7789_CMD_NVGAMCTRL);
    write_data(display, (uint8_t[]){0xD0,0x00,0x02,0x07,0x0A,0x28,0x31,0x54,0x47,0x0E,0x1C,0x17,0x1B,0x1E},14);

    write_command(display, ST7789_CMD_COLMOD);
    write_data_byte(display, 0x55); 

    write_command(display, ST7789_CMD_MADCTL);
    write_data_byte(display, 0x00); 

    write_command(display, ST7789_CMD_VSCRDEF);
    write_data(display, (uint8_t[]){0x00,0x00, (display->height>>8)&0xFF, display->height&0xFF, 0x00},5);

    write_command(display, ST7789_CMD_INVON);

    write_command(display, ST7789_CMD_NORON);
    sleep_ms(10);

    write_command(display, ST7789_CMD_DISPON);
    sleep_ms(100);

    set_blk_high(display);

    st7789_fill_screen(display, ST7789_COLOR_BLACK);
}

void st7789_set_window(st7789_t *display, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
    uint8_t buffer[4];

    x0 += ST7789_OFFSET_X;
    x1 += ST7789_OFFSET_X;
    y0 += ST7789_OFFSET_Y;
    y1 += ST7789_OFFSET_Y;

    if(y1 >= ST7789_OFFSET_Y + display->height) y1 = ST7789_OFFSET_Y + display->height - 1;

    write_command(display, ST7789_CMD_CASET);
    buffer[0] = x0 >> 8;
    buffer[1] = x0;
    buffer[2] = x1 >> 8;
    buffer[3] = x1;
    write_data(display, buffer, sizeof(buffer));

    write_command(display, ST7789_CMD_RASET);
    buffer[0] = y0 >> 8;
    buffer[1] = y0;
    buffer[2] = y1 >> 8;
    buffer[3] = y1;
    write_data(display, buffer, sizeof(buffer));

    write_command(display, ST7789_CMD_RAMWR);
}

void st7789_draw_pixel(st7789_t *display, uint16_t x, uint16_t y, uint16_t color){
    if(x >= display->width || y >= display->height) return;

    st7789_set_window(display, x, y, x, y);
    uint8_t buffer[2] = {color >> 8, color};
    write_data(display, buffer, sizeof(buffer));
}

void st7789_fill_screen(st7789_t *display, uint16_t color){
    st7789_set_window(display, 0, 0, display->width - 1, display->height - 1);
    uint8_t buffer[2] = {color >> 8, color};

    set_dc_data(display);
    set_cs_low(display);

    for(uint32_t i = 0; i < (display->width * display->height); i++) spi_write_blocking(display->spi, buffer, sizeof(buffer));

    set_cs_high(display);
}

void st7789_draw_rectangle(st7789_t *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
    st7789_draw_hline(display, x, y, width, color);               
    st7789_draw_hline(display, x, y + height - 1, width, color); 
    st7789_draw_vline(display, x, y, height, color);             
    st7789_draw_vline(display, x + width - 1, y, height, color); 
}

void st7789_draw_rectangle_filled(st7789_t *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
    st7789_set_window(display, x, y, x + width - 1, y + height - 1);

    uint8_t buffer[2] = { color >> 8, color };

    set_dc_data(display);
    set_cs_low(display);

    for(uint32_t i = 0; i < width * height; i++) spi_write_blocking(display->spi, buffer, sizeof(buffer));

    set_cs_high(display);
}

void st7789_draw_circle(st7789_t *display, uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color) {
    int16_t f = 1 - radius;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * radius;
    int16_t x = 0;
    int16_t y = radius;

    st7789_draw_pixel(display, x0, y0+radius, color);
    st7789_draw_pixel(display, x0, y0-radius, color);
    st7789_draw_pixel(display, x0+radius, y0, color);
    st7789_draw_pixel(display, x0-radius, y0, color);

    while(x<y){
        if(f >= 0){
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        st7789_draw_pixel(display, x0 + x, y0 + y, color);
        st7789_draw_pixel(display, x0 - x, y0 + y, color);
        st7789_draw_pixel(display, x0 + x, y0 - y, color);
        st7789_draw_pixel(display, x0 - x, y0 - y, color);
        st7789_draw_pixel(display, x0 + y, y0 + x, color);
        st7789_draw_pixel(display, x0 - y, y0 + x, color);
        st7789_draw_pixel(display, x0 + y, y0 - x, color);
        st7789_draw_pixel(display, x0 - y, y0 - x, color);
    }
}

void st7789_draw_circle_filled(st7789_t *display, uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color){
    int16_t f = 1 - radius;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * radius;
    int16_t x = 0;
    int16_t y = radius;

    st7789_draw_vline(display, x0, y0 - radius, 2 * radius + 1, color);

    while (x <= y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }

        x++;
        ddF_x += 2;
        f += ddF_x;

        st7789_draw_hline(display, x0 - x, y0 + y, 2 * x + 1, color);
        st7789_draw_hline(display, x0 - x, y0 - y, 2 * x + 1, color);
        st7789_draw_hline(display, x0 - y, y0 + x, 2 * y + 1, color);
        st7789_draw_hline(display, x0 - y, y0 - x, 2 * y + 1, color);
    }
}

void st7789_draw_bitmap(st7789_t *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t *bitmap){
    if(bitmap == NULL) return;

    st7789_set_window(display, x, y, x+width - 1, y+height - 1);
    
    write_command(display, ST7789_CMD_RAMWR);

    set_dc_data(display);
    set_cs_low(display);

    //If bitmap is BIG ENDIAN
    for(int i=0; i<(uint32_t)(width*height); i++){
        uint8_t buffer[2] = { bitmap[i] >> 8, bitmap[i] };
        
        spi_write_blocking(display->spi, buffer, sizeof(buffer));
    }
    
    //If bitmap is LITTLE ENDIAN
    //spi_write_blocking(display->spi, (const uint8_t*)bitmap, (uint32_t)(width*height*sizeof(uint16_t)));
    
    set_cs_high(display);
}

void st7789_draw_hline(st7789_t *display, uint16_t x, uint16_t y, uint16_t length, uint16_t color) {
    if(x + length > display->width) length = display->width - x;

    st7789_set_window(display, x, y, x + length - 1, y);

    uint8_t buffer[2] = { color >> 8, color };
    set_dc_data(display);
    set_cs_low(display);

    for(uint16_t i = 0; i < length; i++) spi_write_blocking(display->spi, buffer, sizeof(buffer));

    set_cs_high(display);
}

void st7789_draw_vline(st7789_t *display, uint16_t x, uint16_t y, uint16_t length, uint16_t color) {
    if(y + length > display->height) length = display->height - y;

    st7789_set_window(display, x, y, x, y + length - 1);

    uint8_t buffer[2] = { color >> 8, color };
    set_dc_data(display);
    set_cs_low(display);

    for(uint16_t i = 0; i < length; i++) spi_write_blocking(display->spi, buffer, sizeof(buffer));

    set_cs_high(display);
}

void st7789_draw_gradient(st7789_t *display, uint16_t gradient_color_start, uint16_t gradient_color_end){
    uint16_t width  = display->width;
    uint16_t height = display->height;
    //Extracting the rgb 5:6:5 values for start and end color.
    uint8_t r0 = (gradient_color_start >> 11) & 0b00011111;
    uint8_t g0 = (gradient_color_start >> 5)  & 0b00111111;
    uint8_t b0 = gradient_color_start & 0b00011111;

    uint8_t r1 = (gradient_color_end >> 11) & 0b00011111;
    uint8_t g1 = (gradient_color_end >> 5)  & 0b00111111;
    uint8_t b1 = gradient_color_end & 0b00011111;

    //Loop through entire height calculating the gradient for each height.
    for(uint16_t y = 0; y < height; y++){
        float transition = (float)y / (height - 1); 
        uint8_t r = r0 + (r1 - r0) * transition;
        uint8_t g = g0 + (g1 - g0) * transition;
        uint8_t b = b0 + (b1 - b0) * transition;

        //Reform the rgb 16 bit value with shifts and or operations.
        uint16_t color = (r << 11) | (g << 5) | b;

        st7789_draw_hline(display, 0, y, width, color);
    }
}