#ifndef GC9A01_H
#define GC9A01_H

#include "pico/stdlib.h"

#include "hardware/spi.h"

typedef struct{
    spi_inst_t *spi;

    uint32_t spi_clk;
    uint16_t width;
    uint16_t height;
    
    uint8_t pin_cs;
    uint8_t pin_dc;
    uint8_t pin_rst;
    uint8_t pin_scl;
    uint8_t pin_sda;

} gc9a01_t;

void gc9a01_init(gc9a01_t *display);
void gc9a01_set_window(gc9a01_t *display, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void gc9a01_draw_pixel(gc9a01_t *display, uint16_t x, uint16_t y, uint16_t color);

void gc9a01_draw_hline(gc9a01_t *display, uint16_t x, uint16_t y, uint16_t w, uint16_t color);
void gc9a01_draw_vline(gc9a01_t *display, uint16_t x, uint16_t y, uint16_t h, uint16_t color);

void gc9a01_draw_rectangle(gc9a01_t *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void gc9a01_draw_rectangle_filled(gc9a01_t *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);

void gc9a01_draw_circle(gc9a01_t *display, uint16_t x_circle, uint16_t y_circle, uint16_t radius, uint16_t color);
void gc9a01_fill_screen(gc9a01_t *display, uint16_t color);

#endif 

/*
gc9a01_t display = {
    .spi     = spi0,
    .spi_clk = TFT_SPI_CLK,
    .width   = TFT_WIDTH,
    .height  = TFT_HEIGHT,
    .pin_cs  = PIN_TFT_CS,
    .pin_dc  = PIN_TFT_DC,
    .pin_rst = PIN_TFT_RST,
    .pin_scl = PIN_TFT_SCL,
    .pin_sda = PIN_TFT_SDA
};
*/